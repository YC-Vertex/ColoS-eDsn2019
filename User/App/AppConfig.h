#ifndef _APP_CONFIG__H_
#define _APP_CONFIG__H_

#include "main.h"
#include "v_MOTOR.h"
#include "v_usartdma.h"
#include "v_MOTION.h"
#include "v_MPU6050.h"
#include "v_EDC21.h"

#define ATTRACT (HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, GPIO_PIN_SET))
#define BREAKUP (HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, GPIO_PIN_RESET))

extern const float speedEps;

extern DMA_InstType debug;
extern DMA_InstType comm;
extern DMA_InstType monitor;
extern EDC21Global_InstType eGlobal;
extern EDC21Player_InstType ePlayer[2];
extern MOTOR_InstType motor[4];
extern MPU6050_InstType mpu;
extern Position_InstType Vehicle;

#endif