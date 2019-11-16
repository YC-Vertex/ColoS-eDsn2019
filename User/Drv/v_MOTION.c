#include "v_MOTION.h"
#define D2R 0.0174532925199433f

static float old;

void setTarget(Position_InstType* pInst, float tarx, float tary,float tarz) {
  pInst->targetX = tarx;
  pInst->targetY = tary;
  pInst->targetZ = tarz;
  pInst->xPrvE = pInst->targetX - pInst->deltaX;
  pInst->yPrvE = pInst->targetY - pInst->deltaY;
  pInst->zPrvE = pInst->targetZ - pInst->deltaZ;
}

void setSpeed(MOTOR_InstType* mt,Position_InstType* pInst, float xSpeed, float ySpeed, float zSpeed) {
  xSpeed /= pInst->xMultiples;
  ySpeed /= pInst->yMultiples;
  zSpeed /= pInst->zMultiples;
  float max = ABS(xSpeed) + ABS(ySpeed)+ ABS(zSpeed), d = 1.f;
  if (max > 500) d = 500 / max;
  MotorSetSpeed(mt + 0, d * (xSpeed + ySpeed + zSpeed));
  MotorSetSpeed(mt + 1, d * (xSpeed - ySpeed - zSpeed));
  MotorSetSpeed(mt + 2, d * (xSpeed - ySpeed + zSpeed));
  MotorSetSpeed(mt + 3, d * (xSpeed + ySpeed - zSpeed));
}

void setCircle(MOTOR_InstType* mt,Position_InstType* pInst, float R,float theta,float time) {
  float xSpeed = theta * R * D2R / time;
  float zspeed = theta / time ; 
  setSpeed(mt,pInst,xSpeed,0,zspeed);
  osDelay((uint32_t)(time*1000));
  setSpeed(mt,pInst,0,0,0);
}

void speedHandler(Position_InstType* pInst, MOTOR_InstType* mt,JY61_InstType* gyro, float dt) {
  pInst->xSpeed = (mt[0].speed + mt[1].speed + mt[2].speed + mt[3].speed) *
                  pInst->xMultiples / 4;
  pInst->ySpeed = (mt[0].speed - mt[1].speed - mt[2].speed + mt[3].speed) *
                  pInst->yMultiples / 4;
  pInst->zSpeed = (mt[0].speed - mt[1].speed + mt[2].speed - mt[3].speed) *
                  pInst->zMultiples / 4;
  
  double c= cos(1.*D2R *pInst->deltaZ),s=sin(1.*D2R *pInst->deltaZ);
  pInst->deltaX += (pInst->xSpeed * c -  pInst->ySpeed *s) * dt;
  pInst->deltaY += (pInst->ySpeed * c +  pInst->xSpeed *s) * dt;
  float nxt=-gyro->yall;
  if(nxt - old < -180) nxt+=360;
  if(nxt - old > 180) nxt-=360;
  pInst->deltaZ += pInst->zSpeed*dt;
  pInst->deltaZ+=(nxt-pInst->deltaZ)/5;
  if(pInst->deltaZ - nxt > 5 )pInst->deltaZ=nxt;
  if(nxt-pInst->deltaZ> 5 )pInst->deltaZ+=pInst->deltaZ=nxt;
  old=nxt;
}

void moveHandler(Position_InstType* pInst, MOTOR_InstType* mt, float dt) {
  pInst->xCurE = pInst->targetX - pInst->deltaX;
  pInst->yCurE = pInst->targetY - pInst->deltaY;
  pInst->zCurE = pInst->targetZ - pInst->deltaZ;
  /*
  float xde = (pInst->xCurE - pInst->xPrvE)/dt;
  float yde = (pInst->yCurE - pInst->yPrvE)/dt;
  if(xCurE > 300) xSetSpeed = 400;
  else if(xCurE > 100) xSetSpeed = xCurE + 100;
  else if(xCurE > -100) xSetSpeed = xCurE * 2;
  else if(xCurE > -300) xSetSpeed = xCurE - 100;
  else if(xCurE < -300) xSetSpeed = -400;

  if(yCurE > 300) ySetSpeed = 400;
  else if(yCurE > 100) ySetSpeed = yCurE + 100;
  else if(yCurE > -100) ySetSpeed = yCurE * 2;
  else if(yCurE > -300) ySetSpeed = yCurE - 100;
  if(yCurE < -300) ySetSpeed = -400;

  pInst-> xSetSpeed =
  pInst->ySetSpeed = */
  
  double c= cos(1.*D2R *pInst->deltaZ),s=sin(1.*D2R *pInst->deltaZ);
  float fakeX=pInst->xKp * pInst->xCurE +
                     pInst->xKd * (pInst->xCurE - pInst->xPrvE) / dt;
  float fakeY=pInst->yKp * pInst->yCurE +
                     pInst->yKd * (pInst->yCurE - pInst->yPrvE) / dt;
  pInst->xSetSpeed = fakeX*c+fakeY*s;
  pInst->ySetSpeed = -fakeX*s+fakeY*c;
  pInst->zSetSpeed = pInst->zKp * pInst->zCurE +
                     pInst->zKd * (pInst->zCurE - pInst->zPrvE) / dt;

  pInst->xPrvE = pInst->xCurE;
  pInst->yPrvE = pInst->yCurE;
  pInst->zPrvE = pInst->zCurE;
}