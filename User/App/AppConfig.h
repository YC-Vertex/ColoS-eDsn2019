#ifndef _APP_CONFIG__H_
#define _APP_CONFIG__H_

#include "main.h"
#include "v_MOTOR.h"
#include "v_usartdma.h"
#include "v_MOTION.h"
#include "v_EVENT.h"
#include "v_EDC21.h"
#include "v_MAP.h"
#include "v_JY61.h"

#define ATTRACT (HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, GPIO_PIN_SET))
#define BREAKUP (HAL_GPIO_WritePin(GREEN_GPIO_Port, GREEN_Pin, GPIO_PIN_RESET))

extern const float speedEps;

extern _Bool startFlag;
extern _Bool carFlag;
extern _Bool navFlag;
extern _Bool mockLaby;
extern _Bool runMap;
extern _Bool forceUpdate;

extern DMA_InstType debug;
extern DMA_InstType comm;
extern DMA_InstType sensor;
extern DMA_InstType monitor;
extern EDC21Global_InstType eGlobal;
extern EDC21Player_InstType ePlayer[2];
extern EDC21Player_InstType* ePlayerPointer;
extern EDC21Map_InstType eMap;
extern MOTOR_InstType motor[4];
extern JY61_InstType jy;
extern Position_InstType Vehicle;

#endif