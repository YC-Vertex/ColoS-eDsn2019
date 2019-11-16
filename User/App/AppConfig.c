#include "AppConfig.h"

_Bool startFlag = 0;
_Bool carFlag = 0; // 0 - A, 1 - B
_Bool navFlag = 0;

uint8_t uart2RxBuf[256];
uint8_t uart3RxBuf[256];
uint8_t uart4RxBuf[256];
uint8_t uart5RxBuf[256];

const float speedEps = 30;

DMA_InstType comm = {
  "comm(u2)", &huart2, &hdma_usart2_rx,
  uart2RxBuf,
  255, 0
};

DMA_InstType debug = {
  "debug(u3)", &huart3, &hdma_usart3_rx,
  uart3RxBuf,
  255, 0
};

DMA_InstType sensor = {
  "snsr(u4)", &huart4, &hdma_uart4_rx,
  uart4RxBuf,
  255, 0
};


DMA_InstType monitor = {
  "mntr(u5)", &huart5, &hdma_uart5_rx,
  uart5RxBuf,
  255, 0
};

EDC21Global_InstType eGlobal = {
  "EDC global",
  0, NONE, {0, 0}, {0, 0}
};

EDC21Player_InstType ePlayer[2] = {
  {
    "player 1",
    0, {0, 0}, 0, {0, 0, 0}, {0, 0, 0}
  }, {
    "player 2",
    0, {0, 0}, 0, {0, 0, 0}, {0, 0, 0}
  }
};

Position_InstType Vehicle = {
  0.f,  0.f,  0.f,    //delta
  .98f, .84f, .35f,  //Mutiple
  0,    0,    0,      //target
  0.f,  0.f,  0.f,    //speed XYZ
  0.f,  0.f,  0.f,    //set speed
  8.f,  8.f,  8.f,   //kp
  1.f,  1.f,  2.f,   //kd
  0.f,  0.f,  0.f,    //curE
  0.f,  0.f,  0.f     //prvE
};

MOTOR_InstType motor[4] = {
  {
    "FL",
    &htim6, &htim1, &htim8, TIM_CHANNEL_1,      // timer, encoder, pwm, pwmchannel
    MTR1_CTR0_GPIO_Port, MTR1_CTR0_Pin, MTR1_CTR1_GPIO_Port, MTR1_CTR1_Pin,
    0, 0, 0, 0,            // lastUpdata, thisU, lastValue, thisV
    1, 0, 0, 0, 0, 0,      // intDir, dir, encRps, motorRps, speed, targetSpd
    52.0, 30.0, 60.0 * PI, // ppr, sdr, perim
    0.8, 0.2, 0.08,        // kp, ki, kd
    0, 0, 0, 0, 0, 0       // prvE, curE, sumE, pidval atWork HaltCounter 
  }, {
    "FR",
    &htim6, &htim3, &htim8, TIM_CHANNEL_2,
    MTR2_CTR0_GPIO_Port, MTR2_CTR0_Pin, MTR2_CTR1_GPIO_Port, MTR2_CTR1_Pin,
    0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0,
    52.0, 30.0, 60.0 * PI,
    0.8, 0.2, 0.08,      
    0, 0, 0, 0, 0, 0
  }, {
    "RL",
    &htim6, &htim4, &htim8, TIM_CHANNEL_3,
    MTR3_CTR0_GPIO_Port, MTR3_CTR0_Pin, MTR3_CTR1_GPIO_Port, MTR3_CTR1_Pin,
    0, 0, 0, 0, 
    1, 0, 0, 0, 0, 0,
    52.0, 30.0, 60.0 * PI,
    0.8, 0.2, 0.08,    
    0, 0, 0, 0, 0, 0
  }, {
    "RR",
    &htim6, &htim5, &htim8, TIM_CHANNEL_4,
    MTR4_CTR0_GPIO_Port, MTR4_CTR0_Pin, MTR4_CTR1_GPIO_Port, MTR4_CTR1_Pin,
    0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0,
    52.0, 30.0, 60.0 * PI,
    0.8, 0.2, 0.08,   
    0, 0, 0, 0, 0, 0
  }
};

JY61_InstType jy = {
  "JY61",
  .0f, .0f, .0f,
  .0f, .0f, .0f,
  .0f, .0f, .0f
};