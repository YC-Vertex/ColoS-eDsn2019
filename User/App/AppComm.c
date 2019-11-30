#include "main.h"
#include "AppConfig.h"

static uint8_t rxBuf[100];
static uint16_t rxBufPtr = 0;
static _Bool isStart = 0;
static char tempBuf[100] = {0};

void DebugTaskDaemon(void const * argument) {
  DmaInit(&comm);
  DmaInit(&debug);
  DmaInit(&sensor);
  DmaInit(&monitor);
  
  osDelay(1000);
  
  while (1) {
    memset(tempBuf, 0, 100);
    uint16_t length = DmaRecv(&debug, tempBuf, 100);
    
    if (length) {
      for (int i = 0; i < length; ++i) {
        
        if (isStart) {
          rxBuf[rxBufPtr++] = tempBuf[i];
          if (rxBuf[rxBufPtr-1] == ';') {
            #ifdef __DEBUG_1__
            printf(">> %s\r\n", rxBuf);
            #endif
            
            if (rxBuf[0] == 'q') { // run quest
              /*
              if (rxBuf[1] == '1') {
                NEout();
              } else if (rxBuf[1] == '2') {
                SWout();
              } else if (rxBuf[1] == '3') {
                setTarget(&Vehicle, 2600, 2600, Vehicle.deltaZ);
                // navFlag = 1;
                WaitTillFinishByLoc(30.f, 3.f);
                // navFlag = 0;
                // setSpeed(motor, &Vehicle, 0, 0, 0);
              } else if (rxBuf[1] == '4') {
                int x, y;
                sscanf(rxBuf, "$q4,%d,%d;", &x, &y);
                setTarget(&Vehicle, x, y, Vehicle.deltaZ);
                ATTRACT;
                // navFlag = 1;
                WaitTillFinishByLoc(30.f, 3.f);
                osDelay(100);
                setTarget(&Vehicle, x, 1200, Vehicle.deltaZ);
                WaitTillFinishByLoc(30.f, 3.f);
                // navFlag = 0;
                BREAKUP;
                // setSpeed(motor, &Vehicle, 0, 0, 0);
              } else if (rxBuf[1] == '5') {
                SWout();
                ATTRACT;
                setTarget(&Vehicle, 240, 160, -90);
                WaitTillFinishByLoc(20.f, 3.f);
                osDelay(800);
                setTarget(&Vehicle, 240, 2000, -90);
                WaitTillFinishByLoc(20.f, 3.f);
              }
              */
              task = rxBuf[1] - '0';
            }
            
            else if (rxBuf[0] == 'x') { // setTarget
              int x, y;
              float angle;
              int t = sscanf(rxBuf, "x%dy%dz%f;", &x, &y, &angle);
              if (t == 3) {
                setTarget(&Vehicle, x, y, angle);
                printf(">> set: %d %d %f\r\n", x, y, angle);
              }
            }
            
            else if (rxBuf[0] == 's') { // setSpeed
              float x, y, angle;
              int t = sscanf(rxBuf, "sx%fy%fz%f;", &x, &y, &angle);
              if (t == 3) {
                navFlag = 0;
                setSpeed(motor, &Vehicle, x, y, angle);
              }
            }
            
            else if (rxBuf[0] == 't') { // setCircle
              float theta, r, time;
              int t = sscanf(rxBuf, "t%fr%ft%f;", &theta, &r, &time);
              setCircle(motor, &Vehicle, theta, r, time);
            }
            
            else if (rxBuf[0] == 'c') { // set car and start, the only way to enter match mode
              char car;
              float angle;
              sscanf(rxBuf, "car%c%f;", &car, &angle);
              if (fabs(angle - 0.f) < 0.2)
                angle = 0.01f;
              if (LocInitByCar(car, angle))
                enableMonitor = 1;
              else
                enableMonitor = 0;
              navFlag = 0;
            }
            
            else if (rxBuf[0] == 'i') { // init by pos + angle
              float x, y, angle;
              int t = sscanf(rxBuf, "ix%fy%fz%f;", &x, &y, &angle);
              if (fabs(angle - 0.f) < 0.2)
                angle = 0.01f;
              if (t == 3) {
                XYPos pos = {x, y};
                LocInitByPos(pos, angle);
                navFlag = 0;
              }
            }
            
            else if (rxBuf[0] == 'l') { // laby test
              if (rxBuf[1] == 'p') { // set target by point index
                int point = -1;
                int t = sscanf(rxBuf, "lp%d;", &point);
                if (t == 1) {
                  setTargetByPoint(&eMap, point);
                }
              }
              else if (rxBuf[1] == 'x') { // set target by point pos
                XYPos pos;
                int t = sscanf(rxBuf, "lx%dy%d;", &(pos.x), &(pos.y));
                if (t == 2) {
                  setTargetByPos(&eMap, pos);
                }
              }
              mockLaby = 1;
              forceUpdate = 1;
            }
            
            else if (rxBuf[0] == '>') { // virtual path finding test
              int cur, tar;
              int t = sscanf(rxBuf, ">%d>%d;", &cur, &tar);
              eMap.curPoint = cur;
              eMap.tarPoint = tar;
              MapHandler(&eMap);
              EdcDispRouteInfo(&eMap);
            }
            
            else if (rxBuf[0] == 'h') { // obstacle debug mode
              int num, index, col, row;
              int mapIndex[2];
              char msg1[64], msg2[64];
              char * msg = msg1;
              char * buf = msg2;
              char * temp;
              
              sscanf(rxBuf, "h%d,%s;", &num, msg);
              if (num == 0) InitMap(&eMap);
              for (int i = 0; i < num; ++i) {
                sscanf(msg, "%d,%s;", &index, buf);
                temp = msg;
                msg = buf;
                buf = temp;
                
                if (index < 30) { // verticle (y dir)
                  col = index % 5;
                  row = index / 5;
                  mapIndex[0] = row * 6 + col;
                  mapIndex[1] = mapIndex[0] + 1;
                  eMap.map[mapIndex[0]] &= 0x0e;
                  eMap.map[mapIndex[1]] &= 0x0d;
                } else { // horizontal (x dir)
                  index -= 30;
                  col = index % 6;
                  row = index / 6;
                  mapIndex[0] = index;
                  mapIndex[1] = index + 6;
                  eMap.map[mapIndex[0]] &= 0x0b;
                  eMap.map[mapIndex[1]] &= 0x07;
                }
                  printf(">> %d %d\r\n", mapIndex[0], mapIndex[1]);
              }
            }
            
            else if (rxBuf[0] == 'm') { // set multiple
              float a, b, c;
              int t = sscanf(rxBuf, "mx%fy%fz%f", &a, &b, &c);
              if (t == 3) {
                Vehicle.xMultiples = a;
                Vehicle.yMultiples = b;
                Vehicle.zMultiples = c;
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
    
    osDelay(63);
  }
}

void MonitorTaskDaemon(void const * argument) {
  uint8_t count = 0;
  
  osDelay(1000);
  
  while (1) {
    EDC21Handler(&monitor, &eGlobal, ePlayer + 0, ePlayer + 1);
    if (enableMonitor && eGlobal.status != START) {
      navFlag = 0;
      setSpeed(motor, &Vehicle, 0, 0, 0);
    }
    #ifdef __DEBUG_1__
    if (count++ >= 40) {
      EdcDispGlobalInfo(&eGlobal);
      EdcDispPlayerInfo(ePlayer + 0);
      EdcDispPlayerInfo(ePlayer + 1);
      EdcDispRouteInfo(&eMap);
      EdcDispMapInfo(&eMap);
      count = 0;
    }
    #endif
    
    osDelay(63);
  }
}