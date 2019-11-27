#ifndef _V_MOTION__H_
#define _V_MOTION__H_

#include "main.h"
#include "v_MOTOR.h"
#include "v_JY61.h"
#include "v_EDC21.h"

typedef struct {
  float deltaX; // current x location
  float deltaY; // current y location
  float deltaZ; // current angle
  float xMultiples;
  float yMultiples; 
  float zMultiples; 
  float targetX;
  float targetY;
  float targetZ;
  float xSpeed;
  float ySpeed;
  float zSpeed;
  float xSetSpeed;
  float ySetSpeed;
  float zSetSpeed;
  float xKp;
  float yKp;
  float zKp;
  float xKd;
  float yKd;
  float zKd;
  float xCurE;
  float yCurE;
  float zCurE;
  float xPrvE;
  float yPrvE;
  float zPrvE;
} Position_InstType;

extern Position_InstType Vehicle;
extern MOTOR_InstType motor[4];
extern JY61_InstType jy;
extern EDC21Global_InstType eGlobal;
extern EDC21Player_InstType ePlayer[2];
extern EDC21Player_InstType* ePlayerPointer;
extern _Bool carFlag;
extern _Bool navFlag;

void speedHandler(Position_InstType* pInst, MOTOR_InstType* mt,JY61_InstType* gyro, float dt);
void moveHandler(Position_InstType* pInst,MOTOR_InstType* mt,float dt);

_Bool LocInit(char car, float angle);
void WaitTillFinishByLoc(float dist, float angle);
void WaitTillFinishBySpd(float speed);
void setTarget(Position_InstType* v, float tarx, float tary, float tarz);
void setSpeed(MOTOR_InstType* mt, Position_InstType* pInst, float xSpeed, float ySpeed, float zSpeed) ;
void setCircle(MOTOR_InstType* mt, Position_InstType* pInst, float theta, float R, float time);
float omegaFusion(float omegaGY,float omegaNav);

#endif
