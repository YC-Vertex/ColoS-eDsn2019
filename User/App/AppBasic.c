#include "main.h"
#include "AppConfig.h"
#include "v_MOTOR.h"
#include "v_MPU6050.h"

void MainTaskDaemon(void const * argument) {
  /*
  uint16_t last_time = 0;
  uint16_t this_time = 0;
  float sum = 0.0f;
  
  osDelay(3000);

  MotorSetSpeed(motor + 0, 600);
  MotorSetSpeed(motor + 1, 600);
  MotorSetSpeed(motor + 2, 600);
  MotorSetSpeed(motor + 3, 600);
  
  for (last_time =  __HAL_TIM_GET_COUNTER(&htim6); ; last_time = this_time) {
    this_time = __HAL_TIM_GET_COUNTER(&htim6);
    int dt = (int)this_time - (int)last_time;
    dt = dt >= 0 ? dt : 0x10000 + dt;
    sum += (motor[0].speed + motor[1].speed + motor[2].speed + motor[3].speed) * dt / 4000000;
  
    if (sum > 1000) {
      MotorSetSpeed(motor + 0, 0);
      MotorSetSpeed(motor + 1, 0);
      MotorSetSpeed(motor + 2, 0);
      MotorSetSpeed(motor + 3, 0);
      while(1);
    }
  
    osDelay(1);
  }
  */
  
  while (1) {
  }
}