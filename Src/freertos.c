/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId MainTaskHandle;
osThreadId SensorTaskHandle;
osThreadId EncoderTaskHandle;
osThreadId LocateTaskHandle;
osThreadId MonitorTaskHandle;
osThreadId DebugTaskHandle;
osThreadId MapTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
   
/* USER CODE END FunctionPrototypes */

void MainTaskDaemon(void const * argument);
void SensorTaskDaemon(void const * argument);
void EncoderTaskDaemon(void const * argument);
void LocateTaskDaemon(void const * argument);
void MonitorTaskDaemon(void const * argument);
void DebugTaskDaemon(void const * argument);
void MapTaskDaemon(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];
  
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}                   
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of MainTask */
  osThreadDef(MainTask, MainTaskDaemon, osPriorityNormal, 0, 128);
  MainTaskHandle = osThreadCreate(osThread(MainTask), NULL);

  /* definition and creation of SensorTask */
  osThreadDef(SensorTask, SensorTaskDaemon, osPriorityAboveNormal, 0, 128);
  SensorTaskHandle = osThreadCreate(osThread(SensorTask), NULL);

  /* definition and creation of EncoderTask */
  osThreadDef(EncoderTask, EncoderTaskDaemon, osPriorityRealtime, 0, 128);
  EncoderTaskHandle = osThreadCreate(osThread(EncoderTask), NULL);

  /* definition and creation of LocateTask */
  osThreadDef(LocateTask, LocateTaskDaemon, osPriorityRealtime, 0, 128);
  LocateTaskHandle = osThreadCreate(osThread(LocateTask), NULL);

  /* definition and creation of MonitorTask */
  osThreadDef(MonitorTask, MonitorTaskDaemon, osPriorityAboveNormal, 0, 128);
  MonitorTaskHandle = osThreadCreate(osThread(MonitorTask), NULL);

  /* definition and creation of DebugTask */
  osThreadDef(DebugTask, DebugTaskDaemon, osPriorityNormal, 0, 128);
  DebugTaskHandle = osThreadCreate(osThread(DebugTask), NULL);

  /* definition and creation of MapTask */
  osThreadDef(MapTask, MapTaskDaemon, osPriorityNormal, 0, 128);
  MapTaskHandle = osThreadCreate(osThread(MapTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_MainTaskDaemon */
/**
  * @brief  Function implementing the MainTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_MainTaskDaemon */
__weak void MainTaskDaemon(void const * argument)
{

  /* USER CODE BEGIN MainTaskDaemon */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END MainTaskDaemon */
}

/* USER CODE BEGIN Header_SensorTaskDaemon */
/**
* @brief Function implementing the SensorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_SensorTaskDaemon */
__weak void SensorTaskDaemon(void const * argument)
{
  /* USER CODE BEGIN SensorTaskDaemon */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END SensorTaskDaemon */
}

/* USER CODE BEGIN Header_EncoderTaskDaemon */
/**
* @brief Function implementing the EncoderTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_EncoderTaskDaemon */
__weak void EncoderTaskDaemon(void const * argument)
{
  /* USER CODE BEGIN EncoderTaskDaemon */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END EncoderTaskDaemon */
}

/* USER CODE BEGIN Header_LocateTaskDaemon */
/**
* @brief Function implementing the LocateTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LocateTaskDaemon */
__weak void LocateTaskDaemon(void const * argument)
{
  /* USER CODE BEGIN LocateTaskDaemon */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END LocateTaskDaemon */
}

/* USER CODE BEGIN Header_MonitorTaskDaemon */
/**
* @brief Function implementing the MonitorTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MonitorTaskDaemon */
__weak void MonitorTaskDaemon(void const * argument)
{
  /* USER CODE BEGIN MonitorTaskDaemon */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END MonitorTaskDaemon */
}

/* USER CODE BEGIN Header_DebugTaskDaemon */
/**
* @brief Function implementing the DebugTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DebugTaskDaemon */
__weak void DebugTaskDaemon(void const * argument)
{
  /* USER CODE BEGIN DebugTaskDaemon */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END DebugTaskDaemon */
}

/* USER CODE BEGIN Header_MapTaskDaemon */
/**
* @brief Function implementing the MapTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_MapTaskDaemon */
__weak void MapTaskDaemon(void const * argument)
{
  /* USER CODE BEGIN MapTaskDaemon */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END MapTaskDaemon */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
