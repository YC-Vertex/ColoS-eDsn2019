#include "main.h"
#include "AppConfig.h"

void SensorTaskDaemon(void const * argument) {
  osDelay(1000);
  // MpuInit();
  osDelay(1000);
  while (1) {
    // MpuDataHandler(&mpu, 1000000);
    printf("mpu: %d\r\n", I2cReadRegister(DEV_ADDR, WHO_AM_I));
    printf("Hello World - SensorTaskDaemon\r\n");
    // osDelay(20);
    osDelay(1000);
  }
}

void EncoderTaskDaemon(void const * argument) {
  osDelay(2000);
  
  MotorInit(motor + 0);
  MotorInit(motor + 1);
  MotorInit(motor + 2);
  MotorInit(motor + 3);
  
  /*
  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1, 800);
  HAL_GPIO_WritePin(MTR1_CTR0_GPIO_Port, MTR1_CTR0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(MTR1_CTR1_GPIO_Port, MTR1_CTR1_Pin, GPIO_PIN_SET);
  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2, 800);
  HAL_GPIO_WritePin(MTR2_CTR0_GPIO_Port, MTR2_CTR0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(MTR2_CTR1_GPIO_Port, MTR2_CTR1_Pin, GPIO_PIN_SET);
  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, 800);
  HAL_GPIO_WritePin(MTR3_CTR0_GPIO_Port, MTR3_CTR0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(MTR3_CTR1_GPIO_Port, MTR3_CTR1_Pin, GPIO_PIN_SET);
  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4, 800);
  HAL_GPIO_WritePin(MTR4_CTR0_GPIO_Port, MTR4_CTR0_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(MTR4_CTR1_GPIO_Port, MTR4_CTR1_Pin, GPIO_PIN_SET);
  */
  
  while (1) {
    MotorSpdHandler(motor + 0, 1000000, 0);
    MotorSpdHandler(motor + 1, 1000000, 0);
    MotorSpdHandler(motor + 2, 1000000, 0);
    MotorSpdHandler(motor + 3, 1000000, 0);
    // osDelay(30-13);
    osDelay(10000);
  }
}