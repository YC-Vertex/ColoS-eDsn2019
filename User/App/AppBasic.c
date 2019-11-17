#include "main.h"
#include "AppConfig.h"

void MainTaskDaemon(void const * argument) {
  uint16_t last_time = 0;
  uint16_t this_time = 0;
  float sum = 0.0f;
  
  osDelay(1000);
  
  ATTRACT; 
  /*
  
  setTarget(&Vehicle, 1050+125, 0, 0);
  osDelay(100);
  while (Vehicle.xSpeed*Vehicle.xSpeed+Vehicle.ySpeed*Vehicle.ySpeed+Vehicle.zSpeed*Vehicle.zSpeed > 1) osDelay(5);
  osDelay(100);
  
  setTarget(&Vehicle, 1650+125, 600, 90);
  osDelay(100);
  while (Vehicle.xSpeed*Vehicle.xSpeed+Vehicle.ySpeed*Vehicle.ySpeed+Vehicle.zSpeed*Vehicle.zSpeed > 1) osDelay(5);
  osDelay(100);
  
  setTarget(&Vehicle, 1650+125, 1050, 90);
  osDelay(100);
  while (Vehicle.xSpeed*Vehicle.xSpeed+Vehicle.ySpeed*Vehicle.ySpeed+Vehicle.zSpeed*Vehicle.zSpeed > 1) osDelay(5);
  osDelay(100);
  
  setTarget(&Vehicle, 1650+125, 900, 90);
  osDelay(100);
  while (Vehicle.xSpeed*Vehicle.xSpeed+Vehicle.ySpeed*Vehicle.ySpeed+Vehicle.zSpeed*Vehicle.zSpeed > 1) osDelay(5);
  osDelay(100);
  */
  
  while (1) {
    osDelay(100000);
  }
}
