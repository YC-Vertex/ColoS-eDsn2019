#ifndef _V_MOTION__H_
#define _V_MOTION__H_

#include "main.h"
#include "v_MOTOR.h"
#include "v_JY61.h"
#include "v_EDC21.h"

typedef struct Position_InstType {
  float deltaX; // current x location
  float deltaY; // current y location
  float deltaZ; // current angle
  float xMultiples, yMultiples, zMultiples;
  float targetX, targetY, targetZ;
  float xSpeed, ySpeed, zSpeed;
  float xSetSpeed, ySetSpeed, zSetSpeed;
  float xKp, yKp, zKp;
  float xKd, yKd, zKd;
  float xCurE, yCurE, zCurE;
  float xPrvE, yPrvE, zPrvE;
} Position_InstType;

extern Position_InstType Vehicle;
extern MOTOR_InstType motor[4];
extern JY61_InstType jy;
extern EDC21Global_InstType eGlobal;
extern EDC21Player_InstType ePlayer[2];
extern EDC21Player_InstType* ePlayerPointer;
extern _Bool carFlag;
extern _Bool navFlag;
extern _Bool enableMonitor;

void speedHandler(Position_InstType* pInst, MOTOR_InstType* mt, JY61_InstType* gyro, float dt);
void moveHandler(Position_InstType* pInst, MOTOR_InstType* mt, float dt);

_Bool LocInitByCar(char car, float angle);
_Bool LocInitByPos(XYPos pos, float angle);
void WaitTillFinishByLoc(float dist, float angle);
void WaitTillFinishBySpd(float speed);
void setTarget(Position_InstType* v, float tarx, float tary, float tarz);
void defaultSetTarget(float tarx, float tary, float d_tarz);
void setSpeed(MOTOR_InstType* mt, Position_InstType* pInst, float xSpeed, float ySpeed, float zSpeed);
void defaultSetSpeed(float xSpeed, float ySpeed, float zSpeed);
void setCircle(MOTOR_InstType* mt, Position_InstType* pInst, float theta, float R, float time);
void defaultSetCircle(float theta, float R, float time);
float omegaFusion(float omegaGY,float omegaNav);

#endif
