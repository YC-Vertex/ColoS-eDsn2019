#include "main.h"
#include "AppConfig.h"

const char * cmdSeq = "x%dy%da%f\r\n";

void CommTaskDaemon(void const * argument) {
  int x, y;
  float angle;
  uint8_t rxBuf[100];
  
  DmaInit(&debug);
  DmaInit(&comm);
  DmaInit(&monitor);
  
  osDelay(1000);
  
  while (1) {
    if (DmaRecv(&debug, rxBuf, 100)) {
      sscanf(rxBuf, cmdSeq, &x, &y, &angle);
      setTarget(&Vehicle, x, y, angle);
      #ifdef __DEBUG_1__
      printf(">> %s", rxBuf);
      printf(">> set: %d %d %f\r\n", x, y, angle);
      #endif
    }
    
    EDC21Handler(&monitor, &eGlobal, ePlayer + 0, ePlayer + 1);
    #ifdef __TEMP__
    EdcDispGlobalInfo(&eGlobal);
    EdcDispPlayerInfo(ePlayer + 0);
    EdcDispPlayerInfo(ePlayer + 1);
    #endif
    osDelay(80);
  }
}