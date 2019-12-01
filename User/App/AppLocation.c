#include "main.h" 
#include "AppConfig.h"

void LocateTaskDaemon(void const * argument) {
  uint8_t count = 0;
  
  for (uint16_t thisTime, lastTime = __HAL_TIM_GET_COUNTER(&htim6); ; osDelay(27)) {
    thisTime = __HAL_TIM_GET_COUNTER(&htim6);
    int dt = (int)thisTime  - (int)lastTime;
    dt = dt >= 0 ? dt : 0x10000 + dt;
    
    if (runMap) {
      if (eMap.length == 0) {
        printf(">> Arrive: %d\r\n", eMap.curPoint);
      } else {
        int point = eMap.route[0];
        if (eMap.curPoint == point && eMap.length >= 2)
          point = eMap.route[1];
        XYPos target = {
          eMap.origin.x + (point % 6) * 300,
          eMap.origin.y + (point / 6) * 300
        };
        printf(">> Target: real%d %d (%d %d)\r\n", point, eMap.route[0], target.x, target.y);
        defaultSetTarget(target.x, target.y, 0);
      }
      runMap = 0;
    }
    
    speedHandler(&Vehicle, motor, &jy, 1.f * dt / 1000000);
    moveHandler(&Vehicle, motor, 1.f * dt / 1000000);
    if (navFlag) {
      setSpeed(motor, &Vehicle, Vehicle.xSetSpeed, Vehicle.ySetSpeed, Vehicle.zSetSpeed);
    }
    
    #ifdef __DEBUG_1__
    if (count++ >= 80) {
      if (!debugFlag) {
        printf("Position: %6.3f %6.3f %6.3f\r\n", Vehicle.deltaX, Vehicle.deltaY, Vehicle.deltaZ);
        // printf("%6.3f %6.3f %6.3f ", Vehicle.xSpeed, Vehicle.ySpeed, Vehicle.zSpeed);
        // printf("%6.3f %6.3f %6.3f\r\n", Vehicle.xSetSpeed, Vehicle.ySetSpeed, Vehicle.zSetSpeed);
        printf("JY: %6.3f %6.3f %6.3f\r\n", jy.pitch, jy.row, jy.yall);
        count = 0;
        debugFlag = 1;
      }
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
    
    osDelay(17);
  }
}
