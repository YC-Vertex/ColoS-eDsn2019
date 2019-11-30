#include "v_EVENT.h"

void NEout(){
  setSpeed(motor, &Vehicle, 500, 0, 0);
  osDelay(500);
  setSpeed(motor, &Vehicle, 0, 0, 0);
  osDelay(200);
  
  setCircle(motor, &Vehicle, 160, 110, 2.5);
  setCircle(motor, &Vehicle, -70, -300, 2);
  /*
  setTarget(&Vehicle, 540, 240, 180);
  navFlag = 1;
  WaitTillFinishByLoc(30.f, 3.f);
  navFlag = 0;
  */
};

void SWout(){
  setSpeed(motor, &Vehicle, 500, 0, 0);
  osDelay(500);
  setSpeed(motor, &Vehicle, 0, 0, 0);
  osDelay(200);
  
  setCircle(motor, &Vehicle, -160, -110, 2.5);
  setCircle(motor, &Vehicle, 70, 300, 2);
  /*
  setTarget(&Vehicle, 240, 540, -90);
  navFlag = 1;
  WaitTillFinishByLoc(30.f, 3.f);
  navFlag = 0;
  */
};