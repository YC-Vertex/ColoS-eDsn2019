#include "main.h"
#include "AppConfig.h"

static uint8_t rxBuf[100];
static uint16_t rxBufPtr = 0;
static _Bool isStart = 0;
static char tempBuf[100] = {0};

void CommTaskDaemon(void const * argument) {
  uint8_t count = 0;
  
  DmaInit(&debug);
  DmaInit(&comm);
  DmaInit(&monitor);
  
  osDelay(1000);
  
  while (1) {
    memset(tempBuf,0,100);
    uint16_t length = DmaRecv(&debug, tempBuf, 100);
    
    if (length) {
      for (int i = 0; i < length; ++i) {
        
        if (isStart) {
          rxBuf[rxBufPtr++] = tempBuf[i];
          if (rxBuf[rxBufPtr-1] == ';') {
            #ifdef __DEBUG_1__
            printf(">> %s", rxBuf);
            #endif
            if (rxBuf[0] == 'x') {
              int x, y;
              float angle;
              int t = sscanf(rxBuf, "x%dy%dz%f;", &x, &y, &angle);
              if(t==3){
                setTarget(&Vehicle, x, y, angle);
                navFlag = 1;
                printf(">> set: %d %d %f\r\n", x, y, angle);
              }
            } else if (rxBuf[0] == 's') {
              float x, y, angle;
              int t = sscanf(rxBuf, "sx%fy%fz%f;", &x, &y, &angle);
              if(t==3){
                setSpeed(motor,&Vehicle, x, y, angle);
                navFlag = 0;
              }
            } else if (rxBuf[0] == 't') {
              float theta, r, time;
              int t = sscanf(rxBuf, "t%fr%ft%f;", &theta, &r, &time);
              setCircle(motor,&Vehicle, r, theta, time);
              navFlag = 0;
            }              
            else if (rxBuf[0] == 'c') {
              char car;
              sscanf(rxBuf, "car%c;", &car);
              startFlag = 1;
              if (car == 'A')
                carFlag = 0;
              else if (car == 'B')
                carFlag = 1;
              else
                startFlag = 0;
            } else if (rxBuf[0] == 'm') {
              float a,b,c;
              int t = sscanf(rxBuf, "mx%fy%fz%f", &a, &b, &c);
              if(t==3){
                Vehicle.xMultiples=a;
                Vehicle.yMultiples=b;
                Vehicle.zMultiples=c;
                printf("set: %f %f %f\r\n", a, b, c);
              }
            }
            memset(rxBuf, 0, 100);
            isStart = 0;
          }
        } else {
          if (tempBuf[i] == '$') {
            rxBufPtr = 0;
            isStart = 1;
          }
        }
        
      }
    }
    
    EDC21Handler(&monitor, &eGlobal, ePlayer + 0, ePlayer + 1);
    /*
    #ifdef __DEBUG_1__
    if (count++ >= 50) {
      EdcDispGlobalInfo(&eGlobal);
      EdcDispPlayerInfo(ePlayer + 0);
      EdcDispPlayerInfo(ePlayer + 1);
      count = 0;
    }
    #endif
    */
    osDelay(80);
  }
}