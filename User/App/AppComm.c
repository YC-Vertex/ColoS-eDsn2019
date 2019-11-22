#include "main.h"
#include "AppConfig.h"

static uint8_t rxBuf[100];
static uint16_t rxBufPtr = 0;
static _Bool isStart = 0;
static char tempBuf[100] = {0};

void CommTaskDaemon(void const * argument) {
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
            if (rxBuf[0] == 'q') { // run quest
              if (rxBuf[1] == '1') {
                NEout();
              } else if (rxBuf[1] == '2') {
                SWout();
              } else if (rxBuf[1] == '3') {
                setTarget(&Vehicle, 2600, 2600, Vehicle.deltaZ);
                navFlag = 1;
                float dx=(Vehicle.deltaX-Vehicle.targetX);
                float dy=(Vehicle.deltaY-Vehicle.targetY);
                float dz=(Vehicle.deltaZ-Vehicle.targetZ);
                while(fabs(dx)+fabs(dy)>60 || fabs(dz)>3){
                  osDelay(100);
                  dx=(Vehicle.deltaX-Vehicle.targetX);
                  dy=(Vehicle.deltaY-Vehicle.targetY);
                  dz=(Vehicle.deltaZ-Vehicle.targetZ);
                }
                navFlag = 0;
                setSpeed(motor,&Vehicle,0,0,0);
              } else if (rxBuf[1] == '4') {
                int x, y;
                sscanf(rxBuf, "$q4,%d,%d;", &x, &y);
                setTarget(&Vehicle, x, y, Vehicle.deltaZ);
                ATTRACT;
                navFlag = 1;
                float dx=(Vehicle.deltaX-Vehicle.targetX);
                float dy=(Vehicle.deltaY-Vehicle.targetY);
                float dz=(Vehicle.deltaZ-Vehicle.targetZ);
                while(fabs(dx)+fabs(dy)>20 || fabs(dz)>3){
                  osDelay(100);
                  dx=(Vehicle.deltaX-Vehicle.targetX);
                  dy=(Vehicle.deltaY-Vehicle.targetY);
                  dz=(Vehicle.deltaZ-Vehicle.targetZ);
                }
                osDelay(100);
                setTarget(&Vehicle, x, 1200, Vehicle.deltaZ);
                dx=(Vehicle.deltaX-Vehicle.targetX);
                dy=(Vehicle.deltaY-Vehicle.targetY);
                dz=(Vehicle.deltaZ-Vehicle.targetZ);
                while(fabs(dx)+fabs(dy)>20 || fabs(dz)>3){
                  osDelay(100);
                  dx=(Vehicle.deltaX-Vehicle.targetX);
                  dy=(Vehicle.deltaY-Vehicle.targetY);
                  dz=(Vehicle.deltaZ-Vehicle.targetZ);
                }
                BREAKUP;
                navFlag = 0;
                setSpeed(motor,&Vehicle,0,0,0);
              }
            } else if (rxBuf[0] == 'x') { // setTarget
              int x, y;
              float angle;
              int t = sscanf(rxBuf, "x%dy%dz%f;", &x, &y, &angle);
              if(t==3){
                setTarget(&Vehicle, x, y, angle);
                navFlag = 1;
                printf(">> set: %d %d %f\r\n", x, y, angle);
              }
            } else if (rxBuf[0] == 's') { // setSpeed
              float x, y, angle;
              int t = sscanf(rxBuf, "sx%fy%fz%f;", &x, &y, &angle);
              if(t==3){
                navFlag = 0;
                setSpeed(motor,&Vehicle, x, y, angle);
              }
            } else if (rxBuf[0] == 't') { // setCircle
              float theta, r, time;
              int t = sscanf(rxBuf, "t%fr%ft%f;", &theta, &r, &time);
              setCircle(motor,&Vehicle,theta, r, time);
              navFlag = 0;
            }              
            else if (rxBuf[0] == 'c') { // set car and start
              char car;
              float angle;
              sscanf(rxBuf, "car%c%f;", &car, &angle);
              Vehicle.deltaZ = angle;
              jy.ydelta += angle- jy.yall;
              Vehicle.deltaX = ePlayerPointer->pos.x;
              Vehicle.deltaY = ePlayerPointer->pos.y;
              startFlag = 1;
              if (car == 'A') {
                carFlag = 0;
                LocInit();
              } else if (car == 'B') {
                carFlag = 1;
                LocInit();
              } else
                startFlag = 0;
            } else if (rxBuf[0] == 'm') { // set multiple
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
    
    osDelay(80);
  }
}

void MonitorTaskDaemon(void const * argument) {
  uint8_t count = 0;
  
  osDelay(1000);
  
  while (1) {
    EDC21Handler(&monitor, &eGlobal, ePlayer + 0, ePlayer + 1);
    if(eGlobal.status != START) setSpeed(motor,&Vehicle,0,0,0);
    #ifdef __DEBUG_1__
    if (count++ >= 20) {
      EdcDispGlobalInfo(&eGlobal);
      EdcDispPlayerInfo(ePlayer + 0);
      EdcDispPlayerInfo(ePlayer + 1);
      count = 0;
    }
    #endif
    
    osDelay(80);
  }
}