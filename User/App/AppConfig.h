#ifndef _APP_CONFIG__H_
#define _APP_CONFIG__H_

#include "main.h"
#include "v_MOTOR.h"
#include "v_usartdma.h"
#include "v_MOTION.h"
#include "v_MPU6050.h"

extern const float speedEps;

extern DMA_InstType dma;
extern MOTOR_InstType motor[4];
extern MPU6050_InstType mpu;
extern Position_InstType Vehicle;

#endif