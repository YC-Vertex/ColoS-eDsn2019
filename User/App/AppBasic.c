#include "main.h"
#include "AppConfig.h"

void MainTaskDaemon(void const * argument) {
  uint16_t last_time = 0;
  uint16_t this_time = 0;
  float sum = 0.0f;
  
  osDelay(1000);
  
  setTarget(&Vehicle,800,400);
  while (1) {
    osDelay(10000000);
  }
}
