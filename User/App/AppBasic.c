#include "main.h"
#include "AppConfig.h"

void MainTaskDaemon(void const * argument) {
  uint16_t last_time = 0;
  uint16_t this_time = 0;
  float sum = 0.0f;
  osDelay(1000);
  setTarget(&Vehicle, 3000, 0,0);
  /*
  setTarget(&Vehicle, 250, 0,0);
  osDelay(100);
  while (Vehicle.xSpeed*Vehicle.xSpeed+Vehicle.ySpeed*Vehicle.ySpeed+Vehicle.zSpeed*Vehicle.zSpeed > 1)osDelay(5);
  osDelay(100);  
  setTarget(&Vehicle, 1600+250, 900,0);
  osDelay(100);
  while (Vehicle.xSpeed*Vehicle.xSpeed+Vehicle.ySpeed*Vehicle.ySpeed+Vehicle.zSpeed*Vehicle.zSpeed > 1)osDelay(5);
  osDelay(100);
  setTarget(&Vehicle,1600+250+350,900,0);*/
  while (1) {
    osDelay(10000000);
  }
}
