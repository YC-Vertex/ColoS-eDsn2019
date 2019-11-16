#ifndef _V_MOTOR__H_
#define _V_MOTOR__H_

#include "main.h"

extern const uint8_t haltThreshold;
typedef struct {
  char * name;
  
  TIM_HandleTypeDef * timeTim;
  TIM_HandleTypeDef * encTim;
  TIM_HandleTypeDef * pwmTim;
  uint32_t pwmChannel;
  GPIO_TypeDef * ctr0Port;
  uint32_t ctr0Pin;
  GPIO_TypeDef * ctr1Port;
  uint32_t ctr1Pin;
  
  uint32_t lastUpdate, thisUpdate;
  uint16_t lastValue, thisValue;
  
  _Bool intDir, dir;
  float encRps, motorRps, speed;
  float targetSpd;
  
  float ppr, sdr, perim; // pulse per encoder round, speed down ratio, diameter
  
  float kp, ki, kd;
  float curE, prvE, sumE;
  float pidval;
  uint8_t atWork;
  uint8_t haltCounter;
} MOTOR_InstType;

void MotorInit(MOTOR_InstType * mInst);
void MotorSetSpeed(MOTOR_InstType * mInst, float spd);
void MotorOutput(MOTOR_InstType * mInst);
void MotorHalt(MOTOR_InstType * mInst);
void MotorSpdHandler(MOTOR_InstType * mInst, uint32_t clkFreq, _Bool isOutput);
void MotorPidHandler(MOTOR_InstType * mInst, float time);

#endif