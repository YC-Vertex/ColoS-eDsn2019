#ifndef _V_MOTION__H_
#define _V_MOTION__H_
#include "main.h"
#include "v_MOTOR.h"
#include "v_JY61.h"

typedef struct {
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
extern Position_InstType Vehicle;
extern MOTOR_InstType motor[4];

void LocateTaskDaemon(void const * argument);
void speedHandler(Position_InstType* pInst, MOTOR_InstType* mt,JY61_InstType* gyro, float dt);
void setTarget(Position_InstType* v,float tarx,float tary,float tarz);
void setSpeed(MOTOR_InstType* mt,Position_InstType* pInst, float xSpeed, float ySpeed, float zSpeed) ;
void moveHandler(Position_InstType* pInst,MOTOR_InstType* mt,float dt);
void setCircle(MOTOR_InstType* mt,Position_InstType* pInst, float R,float theta,float time);
float omegaFusion(float omegaGY,float omegaNav);

#endif
