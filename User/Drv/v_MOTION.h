#ifndef _V_MOTION__H_
#define _V_MOTION__H_
#include "main.h"
#include "v_MOTOR.h"

typedef struct Position_InstType{
  float deltaX;
  float deltaY;
  float xMultiples;
  float yMultiples; 
  float targetX;
  float targetY;
  float xSpeed;
  float ySpeed;
  float xSetSpeed;
  float ySetSpeed;
  float xKp;
  float yKp;
  float xKd;
  float yKd;
  float xCurE;
  float yCurE;
  float xPrvE;
  float yPrvE;
} Position_InstType;

void LocateTaskDaemon(void const * argument);

void speedHandler(Position_InstType* pInst, MOTOR_InstType* mt,float dt);
void setTarget(Position_InstType* v,float tarx,float tary);
void setSpeed(MOTOR_InstType* mt,float xSpeed,float ySpeed);
void moveHandler(Position_InstType* pInst,MOTOR_InstType* mt,float dt);

#endif
