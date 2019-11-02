#ifndef _V_MOTION__H_
#define _V_MOTION__H_
#include "main.h"
#include "v_MOTOR.h"

typedef struct Position_InstType{
  float deltaX;
  float deltaY;
  float deltaZ;
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

void LocateTaskDaemon(void const * argument);

void speedHandler(Position_InstType* pInst, MOTOR_InstType* mt,float dt);
void setTarget(Position_InstType* v,float tarx,float tary,float tarz);
void setSpeed(MOTOR_InstType* mt,float xSpeed,float ySpeed,float zSpeed);
void moveHandler(Position_InstType* pInst,MOTOR_InstType* mt,float dt);

#endif
