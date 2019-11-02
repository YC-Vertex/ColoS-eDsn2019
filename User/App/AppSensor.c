#include "main.h"
#include "AppConfig.h"
#define __DEBUG__

void SensorTaskDaemon(void const * argument) {
  DmaInit(&dma);
  osDelay(1000);
  
  while (1) {
    /*
    if (DmaRecv(&dma)) {
      sscanf(dma.rxBuf, "x: %f\ty: %f\tz: %f\r\n", &mpu.xAngle, &mpu.yAngle, &mpu.zAngle);
      DmaClearBuf(&dma);
      printf("xAngle: %f\tyAngle: %f\tzAngle: %f\r\n", mpu.xAngle, mpu.yAngle, mpu.zAngle);
    }
    osDelay(20-13);
    */
    osDelay(1000);
  }
}

void LocateTaskDaemon(void const * argument) {
 ;
  for( uint16_t thisTime,lastTime = __HAL_TIM_GET_COUNTER(&htim6);;osDelay(1)){
    thisTime=__HAL_TIM_GET_COUNTER(&htim6);
    int dt = (int)thisTime  - (int)lastTime;
    dt = dt >= 0 ? dt : 0x10000 + dt;
    
    speedHandler(&Vehicle,motor,1.f * dt / 1000000);
    moveHandler(&Vehicle,motor,1.f * dt / 1000000);
    setSpeed(motor,Vehicle.xSetSpeed,Vehicle.ySetSpeed);
    
    #ifdef __DEBUG__ 
      printf("Position:\t%6.3f\t%6.3f\t%6.3f\t%6.3f\t%6.3f\t%6.3f\r\n",Vehicle.deltaX,Vehicle.deltaY,Vehicle.xSpeed , Vehicle.ySpeed,Vehicle.xSetSpeed , Vehicle.ySetSpeed);
    #endif
    lastTime=thisTime;
  }
}

void EncoderTaskDaemon(void const * argument) {
  MotorInit(motor + 0);
  MotorInit(motor + 1);
  MotorInit(motor + 2);
  MotorInit(motor + 3);
  
  osDelay(500);
  
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
    for(uint8_t i=0;i<4;i++)
      MotorSpdHandler(motor + i, 1000000, 0);
    for(uint8_t i=0;i<4;i++)
      if(motor[i].atWork)
        MotorOutput(motor + i);
    for(uint8_t i=0;i<4;i++)
      if(motor[i].atWork&&ABS(motor[i].targetSpd)<1e-2){
        if(ABS(motor[i].speed) <= speedEps) motor[i].haltCounter++;
        if(motor[i].haltCounter>haltThreshold)MotorHalt(motor + i);
      }
    
      
      
    osDelay(25-13);
  }
}