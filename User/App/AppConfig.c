#include "AppConfig.h"

uint8_t uart3RxBuf[100];

const float speedEps=30;

DMA_InstType dma = {
  "uart3", &huart3, &hdma_usart3_rx,
  uart3RxBuf,
  100, 0, 0
};

Position_InstType Vehicle = {
  0.f,0.f,    //delta
  1.f,1.1f,  //Mutiple
  0,0,        //target
  0.f,0.f,    //speed
  0.f,0.f,    //set speed
  4.f,4.f,    //kp
  0.4f,0.4f,    //kd
  0.f,0.f,    //curE
  0.f,0.f     //prvE
};

MOTOR_InstType motor[4] = {
  {
    "FrontLeft",
    &htim6, &htim1, &htim8, TIM_CHANNEL_1,      // timer, encoder, pwm, pwmchannel
    MTR1_CTR0_GPIO_Port, MTR1_CTR0_Pin, MTR1_CTR1_GPIO_Port, MTR1_CTR1_Pin,
    0, 0, 0, 0,            // lastUpdata, thisU, lastValue, thisV
    0, 0, 0, 0, 0,         // dir, encRps, motorRps, speed, targetSpd
    52.0, 30.0, 60.0 * PI, // ppr, sdr, perim
    0.8, 0.2, 0.08,        // kp, ki, kd
    0, 0, 0, 0, 0, 0       // prvE, curE, sumE, pidval atWork HaltCounter 
  }, {
    "FrontRight",
    &htim6, &htim3, &htim8, TIM_CHANNEL_2,
    MTR2_CTR0_GPIO_Port, MTR2_CTR0_Pin, MTR2_CTR1_GPIO_Port, MTR2_CTR1_Pin,
    0, 0, 0, 0, 
    0, 0, 0, 0, 0,
    52.0, 30.0, 60.0 * PI,
    0.8, 0.2, 0.08,      
    0, 0, 0, 0, 0, 0
  }, {
    "RearLeft",
    &htim6, &htim4, &htim8, TIM_CHANNEL_3,
    MTR3_CTR0_GPIO_Port, MTR3_CTR0_Pin, MTR3_CTR1_GPIO_Port, MTR3_CTR1_Pin,
    0, 0, 0, 0, 
    0, 0, 0, 0, 0,
    52.0, 30.0, 60.0 * PI,
    0.8, 0.8, 0.08,    
    0, 0, 0, 0, 0, 0
  }, {
    "RearRight",
    &htim6, &htim5, &htim8, TIM_CHANNEL_4,
    MTR4_CTR0_GPIO_Port, MTR4_CTR0_Pin, MTR4_CTR1_GPIO_Port, MTR4_CTR1_Pin,
    0, 0, 0, 0, 
    0, 0, 0, 0, 0,
    52.0, 30.0, 60.0 * PI,
    0.8, 0.2, 0.08,   
    0, 0, 0, 0, 0, 0
  }
};

MPU6050_InstType mpu = {
  "MPU6050",
  &htim6,
  MPU6050_SDA_GPIO_Port, MPU6050_SDA_Pin, MPU6050_SCL_GPIO_Port, MPU6050_SCL_Pin,
  0, 0, 0, 0, 0
};