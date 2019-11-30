#include "main.h"
#include "AppConfig.h"

void SensorTaskDaemon(void const * argument) {
  osDelay(500);
  uint8_t cmd[3] = {0xff, 0xaa, 0x67};
  HAL_UART_Transmit(sensor.usartx, cmd, 3, 2000);  
  osDelay(200);
  cmd[2] = 0x52;
  HAL_UART_Transmit(sensor.usartx, cmd, 3, 2000);
  osDelay(200);
  
  while (1) {
    uint8_t tempBuf[256] = {0};
    uint16_t length = DmaRecv(&sensor, tempBuf, 44);
    
    if (length) {
      for (int i = 0; i < length - 11; ++i) {
        if (tempBuf[i] == 0x55) {
          
          uint8_t sum = 0;
          for (int j = 0; j < 10; ++j) {
            sum += tempBuf[i+j];
          }
          if (tempBuf[i+10] == sum) {
            if (tempBuf[i+1] == 0x51) {
              int16_t x, y, z;
              float xf, yf, zf;
              x = ((int16_t)tempBuf[i+3] << 8) | tempBuf[i+2];
              y = ((int16_t)tempBuf[i+5] << 8) | tempBuf[i+4];
              z = ((int16_t)tempBuf[i+7] << 8) | tempBuf[i+6];
              xf = x / 32768.f * 16.f * 9.8f;
              yf = y / 32768.f * 16.f * 9.8f;
              zf = z / 32768.f * 16.f * 9.8f;
              jy.aX = xf;
              jy.aY = yf;
              jy.aZ = zf;
              #ifdef __DEBUG_2__
              printf("aX%f aY%f aZ%f\r\n", jy.aX, jy.aY, jy.aZ);
              #endif
            } 
            else if (tempBuf[i+1] == 0x52) {
              int16_t x, y, z;
              float xf, yf, zf;
              x = ((int16_t)tempBuf[i+3] << 8) | tempBuf[i+2];
              y = ((int16_t)tempBuf[i+5] << 8) | tempBuf[i+4];
              z = ((int16_t)tempBuf[i+7] << 8) | tempBuf[i+6];
              xf = x / 32768.f * 2000.f;
              yf = y / 32768.f * 2000.f;
              zf = z / 32768.f * 2000.f;
              jy.gX = xf;
              jy.gY = yf;
              jy.gZ = zf;
              #ifdef __DEBUG_2__
              printf("gX%f gY%f gZ%f\r\n", jy.gX, jy.gY, jy.gZ);
              #endif
            } 
            else if (tempBuf[i+1] == 0x53) {
              int16_t r, p, y;
              float rf, pf, yf;
              r = ((int16_t)tempBuf[i+3] << 8) | tempBuf[i+2];
              p = ((int16_t)tempBuf[i+5] << 8) | tempBuf[i+4];
              y = ((int16_t)tempBuf[i+7] << 8) | tempBuf[i+6];
              rf = r / 32768.f * 180.f;
              pf = p / 32768.f * 180.f;
              yf = - y / 32768.f * 180.f;
              jy.row = rf + jy.rdelta;
              jy.pitch = pf + jy.pdelta;
              jy.yall = yf + jy.ydelta;
              #ifdef __DEBUG_2__
              printf("r%f p%f y%f\r\n", jy.row, jy.pitch, jy.yall);
              #endif
            }
            else
              continue;
            i += 10;
          }
          else {
            printf("SUMERROR");
            continue;
          }
          
        }
      }
    }
    
    osDelay(53);
  }
}

int obstacle[4];
void MapTaskDaemon(void const * argument) {
  InitMap(&eMap);
  osDelay(1000);
  int lastTarget = eMap.tarPoint;
  
  while (1) {
    uint8_t tempBuf[256] = {0};
    uint16_t length = DmaRecv(&comm, tempBuf, 255);
    
    XYPos car = {Vehicle.deltaX, Vehicle.deltaY};
    _Bool updateFlag = 0;
    if (lastTarget != eMap.tarPoint)
      updateFlag = 1;
    lastTarget = eMap.tarPoint;
    if (UpdatePos(&eMap, car))
      updateFlag = 1;
    
    /*
    if (length) {
      if (tempBuf[0] == '+') {
        // 判断是否获取了完整的数据
        _Bool isEnd = 0;
        for (int i = 0; i < length; ++i) {
          if (tempBuf[i] == ';') {
            isEnd = 1;
            break;
          }
        }
        // 如果获取了完整的数据
        if (isEnd) {
          int t = sscanf(tempBuf, "+%d-%d<%d>%d;%*s", obstacle+0, obstacle+1, obstacle+2, obstacle+3);
          if (t == 4) {
            
            // if (ePlayerPointer->isInLaby || mockLaby) {
            if (mockLaby) {
              if (UpdateMap(&eMap, car, obstacle, Vehicle.deltaZ)) updateFlag = 1;
            }
            
            #ifdef __DEBUG_2__
            printf("dist: %d %d %d %d\r\n", obstacle[0], obstacle[1], obstacle[2], obstacle[3]);
            #endif
          }
        }
      }
    }
    */
    
    if (forceUpdate || (updateFlag && ((enableMonitor && ePlayerPointer->isInLaby) || mockLaby))) {
      forceUpdate = 0;
      if (MapHandler(&eMap)) {
        runMap = 1;
        osDelay(53);
        WaitTillFinishByLoc(40.f, 4.f);
      }
    } else {
      runMap = 0;
    }
    
    // 需要稍快，保证图搜索时间(?)
    osDelay(43);
  }
}
