#ifndef _V_MPU6050__H_
#define _V_MPU6050__H_

#include "main.h"
#include "v_i2c.h"

#define DEV_ADDR 0x68

#define SMPLRT_DIV 0x19
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C

#define ACCEL_XOUT_H 0x3B 
#define ACCEL_XOUT_L 0x3C 
#define ACCEL_YOUT_H 0x3D 
#define ACCEL_YOUT_L 0x3E 
#define ACCEL_ZOUT_H 0x3F 
#define ACCEL_ZOUT_L 0x40 

#define TEMP_OUT_H 0x41 
#define TEMP_OUT_L 0x42 

#define GYRO_XOUT_H 0x43
#define GYRO_XOUT_L 0x44 
#define GYRO_YOUT_H 0x45 
#define GYRO_YOUT_L 0x46 
#define GYRO_ZOUT_H 0x47 
#define GYRO_ZOUT_L 0x48 

#define PWR_MGMT_1 0x6B
#define WHO_AM_I 0x75

typedef struct {
  char * name;
  
  TIM_HandleTypeDef * timeTim;
  GPIO_TypeDef * sdaPort;
  uint32_t sdaPin;
  GPIO_TypeDef * sclPort;
  uint32_t sclPin;
  
  uint16_t lastUpdate, thisUpdate;
  float xAngle, yAngle, zAngle;
} MPU6050_InstType;

void MpuInit();
uint16_t MpuGetRawData(uint8_t reg_addr);
void MpuGetAngle(MPU6050_InstType * mpuInst, float * buf);
float MpuGetXAngle(MPU6050_InstType * mpuInst);
float MpuGetYAngle(MPU6050_InstType * mpuInst);
float MpuGetZAngle(MPU6050_InstType * mpuInst);

void MpuDataHandler(MPU6050_InstType * mInst, uint32_t clkFreq);

#endif

