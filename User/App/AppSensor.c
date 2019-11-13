#include "main.h"
#include "AppConfig.h"

void SensorTaskDaemon(void const * argument) {
  
  osDelay(1000);
  
  while (1) {
    osDelay(100000);
  }
}
