#include "v_MOTOR.h"

void MotorInit(MOTOR_InstType * mInst) {
  mInst->targetSpd = 0;
  mInst->lastUpdate = __HAL_TIM_GET_COUNTER(mInst->timeTim);
  mInst->lastValue = __HAL_TIM_GET_COUNTER(mInst->encTim);
  __HAL_TIM_SET_COMPARE(mInst->pwmTim, mInst->pwmChannel, 0);
}

void MotorSetSpeed(MOTOR_InstType * mInst, float spd) {
  mInst->targetSpd = spd;
  mInst->sumE = 0;
  mInst->prvE = mInst->targetSpd - mInst->speed;
}

void MotorOutput(MOTOR_InstType * mInst) {
  if (mInst->pidval > 0) {
    HAL_GPIO_WritePin(mInst->ctr0Port, mInst->ctr0Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(mInst->ctr1Port, mInst->ctr1Pin, GPIO_PIN_SET);
    __HAL_TIM_SET_COMPARE(mInst->pwmTim, mInst->pwmChannel, mInst->pidval);
  } else {
    HAL_GPIO_WritePin(mInst->ctr0Port, mInst->ctr0Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(mInst->ctr1Port, mInst->ctr1Pin, GPIO_PIN_RESET);
    __HAL_TIM_SET_COMPARE(mInst->pwmTim, mInst->pwmChannel, -mInst->pidval);
  }
}



void MotorSpdHandler(MOTOR_InstType * mInst, uint32_t clkFreq, _Bool isOutput) {
  uint32_t time;
  uint16_t value;
  
  mInst->thisUpdate = __HAL_TIM_GET_COUNTER(mInst->timeTim);
  mInst->thisValue = __HAL_TIM_GET_COUNTER(mInst->encTim);
  mInst->dir = !__HAL_TIM_IS_TIM_COUNTING_DOWN(mInst->encTim);
  
  time = mInst->thisUpdate >= mInst->lastUpdate ? 
    (mInst->thisUpdate - mInst->lastUpdate) : (0x10000 + mInst->thisUpdate - mInst->lastUpdate);
  value = mInst->thisValue >= mInst->lastValue ? 
    (mInst->thisValue - mInst->lastValue) : (0x10000 + mInst->thisValue - mInst->lastValue);
  value = mInst->dir ? value : 0x10000 - value;
  if (0xffff - time <= 6) time = 0;   // eliminate glitch (?)
  if (value >= mInst->ppr * mInst->sdr * 25) value = 0; // eliminate glitch (?)
  
  mInst->encRps = value / mInst->ppr * clkFreq / time;
  mInst->encRps = mInst->dir ? mInst->encRps : -mInst->encRps;
  mInst->motorRps = mInst->encRps / mInst->sdr;
  mInst->speed = mInst->motorRps * mInst->perim;
  
  printf("%s\t%d\t%f\t%f\r\n", mInst->name, time, mInst->speed, mInst->pidval);
  MotorPidHandler(mInst, 1.0 * time / clkFreq);
  
  if (isOutput == 1) {
    MotorOutput(mInst);
  }
  
  mInst->lastUpdate = mInst->thisUpdate;
  mInst->lastValue = mInst->thisValue;
}

void MotorPidHandler(MOTOR_InstType * mInst, float time) {
  mInst->curE = mInst->targetSpd - mInst->speed;
  mInst->sumE +=  mInst->curE * time;
  if (mInst->sumE > 1e4) mInst->sumE = 1e4;
  else if (mInst->sumE < -1e4) mInst->sumE = -1e4;
  
  mInst->pidval += mInst->kp * mInst->curE + mInst->kd * (mInst->curE - mInst->prvE) / time + mInst->ki * mInst->sumE;
  // printf("\t%f\t%f\t%f\r\n", mInst->kp * mInst->curE , mInst->sumE * mInst->ki , mInst->kd * (mInst->curE - mInst->prvE) / time);
  if (mInst->pidval > 1000) mInst->pidval = 1000;
  if (mInst->pidval < -1000) mInst->pidval = -1000;
  
  mInst->prvE = mInst->curE;
}