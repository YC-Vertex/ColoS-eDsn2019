#include "main.h"
#include "AppConfig.h"

void LocateTaskDaemon(void const * argument) {
  int count = 0;
  
  for (uint16_t thisTime, lastTime = __HAL_TIM_GET_COUNTER(&htim6); ; osDelay(37)) {
    thisTime = __HAL_TIM_GET_COUNTER(&htim6);
    int dt = (int)thisTime  - (int)lastTime;
    dt = dt >= 0 ? dt : 0x10000 + dt;
    
    speedHandler(&Vehicle, motor, 1.f * dt / 1000000);
    moveHandler(&Vehicle, motor, 1.f * dt / 1000000);
    setSpeed(motor, Vehicle.xSetSpeed, Vehicle.ySetSpeed, Vehicle.zSetSpeed);
    
    #ifdef __DEBUG_1__ 
    if (count++ >= 100) {
      printf("Position: %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f %6.3f\r\n",
          Vehicle.deltaX, Vehicle.deltaY, Vehicle.deltaZ, 
          Vehicle.xSpeed, Vehicle.ySpeed, Vehicle.zSpeed,
          Vehicle.xSetSpeed, Vehicle.ySetSpeed, Vehicle.zSetSpeed);
      count = 0;
    }
    #endif
    
    lastTime = thisTime;
  }
}

void EncoderTaskDaemon(void const * argument) {
  MotorInit(motor + 0);
  MotorInit(motor + 1);
  MotorInit(motor + 2);
  MotorInit(motor + 3);
  
  osDelay(500);
  
  while (1) {
    for (uint8_t i = 0; i < 4; i++)
      MotorSpdHandler(motor + i, 1000000, 0);
    
    for (uint8_t i = 0; i < 4; i++)
      if (motor[i].atWork)
        MotorOutput(motor + i);
      
    for (uint8_t i = 0; i < 4; i++) {
      if (motor[i].atWork && ABS(motor[i].targetSpd) < 1e-2) {
        if (ABS(motor[i].speed) <= speedEps)
          motor[i].haltCounter++;
        if (motor[i].haltCounter > haltThreshold)
          MotorHalt(motor + i);
      }
    }
    
    osDelay(7);
  }
}