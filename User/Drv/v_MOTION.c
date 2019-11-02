#include "v_MOTION.h"

extern Position_InstType Vehicle;
extern MOTOR_InstType motor[4];

void setTarget(Position_InstType* pInst, float tarx, float tary) {
  pInst->targetX = tarx;
  pInst->targetY = tary;
  pInst->xPrvE = pInst->targetX - pInst->deltaX;
  pInst->yPrvE = pInst->targetY - pInst->deltaY;
}

void setSpeed(MOTOR_InstType* mt, float xSpeed, float ySpeed) {
  float max = ABS(xSpeed) + ABS(xSpeed), d = 1.f;
  if (max > 600) d = 600 / max;
  MotorSetSpeed(mt + 0, d * (xSpeed + ySpeed));
  MotorSetSpeed(mt + 1, d * (xSpeed - ySpeed));
  MotorSetSpeed(mt + 2, d * (xSpeed - ySpeed));
  MotorSetSpeed(mt + 3, d * (xSpeed + ySpeed));
}

void speedHandler(Position_InstType* pInst, MOTOR_InstType* mt, float dt) {
  pInst->xSpeed = (mt[0].speed + mt[1].speed + mt[2].speed + mt[3].speed) *
                  pInst->xMultiples / 4;
  pInst->ySpeed = (mt[0].speed - mt[1].speed - mt[2].speed + mt[3].speed) *
                  pInst->yMultiples / 4;
  pInst->deltaX += pInst->xSpeed * dt;
  pInst->deltaY += pInst->ySpeed * dt;
}

void moveHandler(Position_InstType* pInst, MOTOR_InstType* mt, float dt) {
  pInst->xCurE = pInst->targetX - pInst->deltaX;
  pInst->yCurE = pInst->targetY - pInst->deltaY;
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
  pInst->xSetSpeed = pInst->xKp * pInst->xCurE +
                     pInst->xKd * (pInst->xCurE - pInst->xPrvE) / dt;
  pInst->ySetSpeed = pInst->yKp * pInst->yCurE +
                     pInst->yKd * (pInst->yCurE - pInst->yPrvE) / dt;

  pInst->xPrvE = pInst->xCurE;
  pInst->yPrvE = pInst->yCurE;
}