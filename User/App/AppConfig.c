#include "AppConfig.h"

MOTOR_InstType motor[4] = {
  {
    "FrontLeft",
    &htim6, &htim1, &htim8, TIM_CHANNEL_1,      // timer, encoder, pwm, pwmchannel
    MTR1_CTR0_GPIO_Port, MTR1_CTR0_Pin, MTR1_CTR1_GPIO_Port, MTR1_CTR1_Pin,
    0, 0, 0, 0,         // lastUpdata, thisU, lastValue, thisV
    0, 0, 0, 0, 0,      // dir, encRps, motorRps, speed, targetSpd
    52.0, 30.0, 56.0 * 3.1415926,               // ppr, sdr, perim
    0.35, 0, 0.03,      // kp, ki, kd
    0, 0, 0, 0          // prvE, curE, sumE, pidval
  }, {
    "FrontRight",
    &htim6, &htim3, &htim8, TIM_CHANNEL_2,
    MTR2_CTR0_GPIO_Port, MTR2_CTR0_Pin, MTR2_CTR1_GPIO_Port, MTR2_CTR1_Pin,
    0, 0, 0, 0, 
    0, 0, 0, 0, 0,
    52.0, 30.0, 56.0 * 3.1415926,
    0.35, 0, 0.03,
    0, 0, 0, 0
  }, {
    "RearLeft",
    &htim6, &htim4, &htim8, TIM_CHANNEL_3,
    MTR3_CTR0_GPIO_Port, MTR3_CTR0_Pin, MTR3_CTR1_GPIO_Port, MTR3_CTR1_Pin,
    0, 0, 0, 0, 
    0, 0, 0, 0, 0,
    52.0, 30.0, 56.0 * 3.1415926,
    0.35, 0, 0.03,
    0, 0, 0, 0
  }, {
    "RearRight",
    &htim6, &htim5, &htim8, TIM_CHANNEL_4,
    MTR4_CTR0_GPIO_Port, MTR4_CTR0_Pin, MTR4_CTR1_GPIO_Port, MTR4_CTR1_Pin,
    0, 0, 0, 0, 
    0, 0, 0, 0, 0,
    52.0, 30.0, 56.0 * 3.1415926,
    0.35, 0, 0.03,
    0, 0, 0, 0
  }
};

MPU6050_InstType mpu = {
  "MPU6050",
  &htim6,
  MPU6050_SDA_GPIO_Port, MPU6050_SDA_Pin, MPU6050_SCL_GPIO_Port, MPU6050_SCL_Pin,
  0, 0, 0, 0, 0
};