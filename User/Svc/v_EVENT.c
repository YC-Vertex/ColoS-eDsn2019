#include "v_EVENT.h"

void NEout(){
  setSpeed(motor,&Vehicle,200,0,0);
  osDelay(1000);
  setSpeed(motor,&Vehicle,0,0,0);
  osDelay(500);
  setCircle(motor,&Vehicle,160,103,3.5);
  setCircle(motor,&Vehicle,-70,-300,4);
  setTarget(&Vehicle,540,240,180);
  navFlag = 1;
  float dx=(Vehicle.deltaX-Vehicle.targetX);
  float dy=(Vehicle.deltaY-Vehicle.targetY);
  float dz=(Vehicle.deltaZ-Vehicle.targetZ);
  while(fabs(dx)+fabs(dy)>60 || fabs(dz)>5){
    osDelay(100);
    dx=(Vehicle.deltaX-Vehicle.targetX);
    dy=(Vehicle.deltaY-Vehicle.targetY);
    dz=(Vehicle.deltaZ-Vehicle.targetZ);
  }
  navFlag = 0;
  return;
  
};

void SWout(){
  
  setSpeed(motor,&Vehicle,200,0,0);
  osDelay(1000);
  setSpeed(motor,&Vehicle,0,0,0);
  osDelay(500);
  setCircle(motor,&Vehicle,-160,-103,3.5);
  setCircle(motor,&Vehicle,70,300,4);
  setTarget(&Vehicle,240,540,-90);
  navFlag = 1;
  float dx=(Vehicle.deltaX-Vehicle.targetX);
  float dy=(Vehicle.deltaY-Vehicle.targetY);
  float dz=(Vehicle.deltaZ-Vehicle.targetZ);
  while(fabs(dx)+fabs(dy)>60 || fabs(dz)>5){
    osDelay(100);
    dx=(Vehicle.deltaX-Vehicle.targetX);
    dy=(Vehicle.deltaY-Vehicle.targetY);
    dz=(Vehicle.deltaZ-Vehicle.targetZ);
  }
  navFlag = 0;
};