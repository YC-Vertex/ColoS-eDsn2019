#include "main.h"
#include "AppConfig.h"

void MainTaskDaemon(void const * argument) {
  uint16_t last_time = 0;
  uint16_t this_time = 0;
  float sum = 0.0f;
  
  osDelay(1000);
  
  // ATTRACT;
  
  while (task == 0) osDelay(500);
  
  while (1) {
    while (task == 0) osDelay(800);
    
    if (task == 1) { // task one: no laby SW task
      SWout();
      ATTRACT;
      ToCollection();
      setTarget(&Vehicle, 200, 2100, -90.f);
      WaitTillFinishByLoc(30.f, 3.f);
      setCircle(motor, &Vehicle, -90, 250, 2);
      ToP1();
      ToP2();
      ToSWgarage();
    } else if (task == 2) { // task two: laby SW task
      SWout();
      ATTRACT;
      ToCollection();
      ToLeftEntry(1);
      
      setTarget(&Vehicle, 550, 850, 0.f);
      WaitTillFinishByLoc(20.f, 2.f);
      setTargetByPoint(&eMap, 34);
      while (!eMap.done) osDelay(200);
      
      ToBottomEntry(0);
      ToP1();
      ToP2();
      ToSWgarage();
    } else if (task == 3) { // task three: laby NE task
      ToP4();
      ToP3();
      ToRightEntry(1);
      
      setTarget(&Vehicle, 2050, 1750, 180.f);
      WaitTillFinishByLoc(20.f, 2.f);
      
      _Bool flag = 0;
      while (1) {
        setTargetByPos(&eMap, eGlobal.person[(int)flag + 1]);
        while (!eMap.done) osDelay(200);
        flag = !flag;
      }
    }
    
    task = 0;
  }
}
