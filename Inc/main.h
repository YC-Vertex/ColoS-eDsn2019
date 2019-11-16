/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "cmsis_os.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
#define PI 3.1415926
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define __DEBUG_1__ // common debug info
// #define __DEBUG_2__ // detail debug info
#define __TEMP__
#define ABS(x) ((x) > 0 ? (x) : (-(x)))
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
int fputc(int ch, FILE *f);
void DelayUs(uint16_t nus);
void DelayMs(uint16_t nms);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define MTR1_CTR0_Pin GPIO_PIN_0
#define MTR1_CTR0_GPIO_Port GPIOF
#define MTR1_CTR1_Pin GPIO_PIN_1
#define MTR1_CTR1_GPIO_Port GPIOF
#define MTR2_CTR0_Pin GPIO_PIN_2
#define MTR2_CTR0_GPIO_Port GPIOF
#define MTR2_CTR1_Pin GPIO_PIN_3
#define MTR2_CTR1_GPIO_Port GPIOF
#define MTR3_CTR0_Pin GPIO_PIN_4
#define MTR3_CTR0_GPIO_Port GPIOF
#define MTR3_CTR1_Pin GPIO_PIN_5
#define MTR3_CTR1_GPIO_Port GPIOF
#define MTR4_CTR0_Pin GPIO_PIN_6
#define MTR4_CTR0_GPIO_Port GPIOF
#define MTR4_CTR1_Pin GPIO_PIN_7
#define MTR4_CTR1_GPIO_Port GPIOF
#define MTR4_ENC0_Pin GPIO_PIN_0
#define MTR4_ENC0_GPIO_Port GPIOA
#define MTR4_ENC1_Pin GPIO_PIN_1
#define MTR4_ENC1_GPIO_Port GPIOA
#define COMM_TX_Pin GPIO_PIN_2
#define COMM_TX_GPIO_Port GPIOA
#define COMM_RX_Pin GPIO_PIN_3
#define COMM_RX_GPIO_Port GPIOA
#define MTR2_ENC0_Pin GPIO_PIN_6
#define MTR2_ENC0_GPIO_Port GPIOA
#define MTR2_ENC1_Pin GPIO_PIN_7
#define MTR2_ENC1_GPIO_Port GPIOA
#define GREEN_Pin GPIO_PIN_1
#define GREEN_GPIO_Port GPIOG
#define MTR1_ENC0_Pin GPIO_PIN_9
#define MTR1_ENC0_GPIO_Port GPIOE
#define MTR1_ENC1_Pin GPIO_PIN_11
#define MTR1_ENC1_GPIO_Port GPIOE
#define DEBUG_TX_Pin GPIO_PIN_10
#define DEBUG_TX_GPIO_Port GPIOB
#define DEBUG_RX_Pin GPIO_PIN_11
#define DEBUG_RX_GPIO_Port GPIOB
#define MTR3_ENC0_Pin GPIO_PIN_12
#define MTR3_ENC0_GPIO_Port GPIOD
#define MTR3_ENC1_Pin GPIO_PIN_13
#define MTR3_ENC1_GPIO_Port GPIOD
#define IR1_Pin GPIO_PIN_2
#define IR1_GPIO_Port GPIOG
#define IR2_Pin GPIO_PIN_3
#define IR2_GPIO_Port GPIOG
#define IR3_Pin GPIO_PIN_4
#define IR3_GPIO_Port GPIOG
#define IR4_Pin GPIO_PIN_5
#define IR4_GPIO_Port GPIOG
#define IR5_Pin GPIO_PIN_6
#define IR5_GPIO_Port GPIOG
#define MTR1_PWM_Pin GPIO_PIN_6
#define MTR1_PWM_GPIO_Port GPIOC
#define MTR2_PWM_Pin GPIO_PIN_7
#define MTR2_PWM_GPIO_Port GPIOC
#define MTR3_PWM_Pin GPIO_PIN_8
#define MTR3_PWM_GPIO_Port GPIOC
#define MTR4_PWM_Pin GPIO_PIN_9
#define MTR4_PWM_GPIO_Port GPIOC
#define JY61_TX_Pin GPIO_PIN_10
#define JY61_TX_GPIO_Port GPIOC
#define JY61_RX_Pin GPIO_PIN_11
#define JY61_RX_GPIO_Port GPIOC
#define MONITOR_TX_Pin GPIO_PIN_12
#define MONITOR_TX_GPIO_Port GPIOC
#define MONITOR_RX_Pin GPIO_PIN_2
#define MONITOR_RX_GPIO_Port GPIOD
#define PIN1_Pin GPIO_PIN_4
#define PIN1_GPIO_Port GPIOB
#define PIN2_Pin GPIO_PIN_5
#define PIN2_GPIO_Port GPIOB
#define PIN3_Pin GPIO_PIN_6
#define PIN3_GPIO_Port GPIOB
#define PIN4_Pin GPIO_PIN_7
#define PIN4_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
