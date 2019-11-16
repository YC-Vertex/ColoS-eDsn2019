#include "v_EDC21.h"

static uint16_t rxBufPtr = 0;
static uint8_t rxBuf[128];
static _Bool isStart = 0;

_Bool Decode(uint8_t * data, EDC21Global_InstType * gb,
  EDC21Player_InstType * p1, EDC21Player_InstType * p2) {
    
  if (data[30] != 0x0d || data[31] != 0x0a) {
    return 0;
  }
  
  // global
  gb->time = (data[0] << 8) | data[1];
  if (data[2] & 0x80) {
    if (data[2] & 0x40)
      gb->status = END;   // 11
    else
      gb->status = PAUSE; // 10
  } else {
    if (data[2] & 0x40)
      gb->status = START; // 01
    else
      gb->status = NONE;  // 00
  }
  gb->person[0].x = ((data[3] & 0x80)) << 1 | data[8];
  gb->person[0].y = ((data[3] & 0x40)) << 2 | data[9];
  gb->person[1].x = ((data[3] & 0x20)) << 3 | data[10];
  gb->person[1].y = ((data[3] & 0x10)) << 4 | data[11];
  gb->ball.x = ((data[3] & 0x08)) << 5 | data[12];
  gb->ball.y = ((data[3] & 0x04)) << 6 | data[13];

  // player 1
  p1->isInLaby = (data[2] & 0x20) >> 5;
  p1->pos.x = ((data[2] & 0x08) << 5) | data[4];
  p1->pos.y = ((data[2] & 0x04) << 6) | data[5];
  p1->score = (data[14] << 8) | data[15];
  p1->count[0] = data[18];
  p1->count[1] = data[20];
  p1->count[2] = data[22];

  // player 2
  p2->isInLaby = (data[2] & 0x10) >> 4;
  p2->pos.x = ((data[2] & 0x02) << 7) | data[6];
  p2->pos.y = ((data[2] & 0x01) << 8) | data[7];
  p2->score = (data[16] << 8) | data[17];
  p2->count[0] = data[19];
  p2->count[1] = data[21];
  p2->count[2] = data[23];
  
  return 1;
}



void EDC21Handler(DMA_InstType * dma, EDC21Global_InstType * gb,
  EDC21Player_InstType * p1, EDC21Player_InstType * p2) {
    
  uint8_t tempBuf[100] = {0};
  uint16_t length = DmaRecv(dma, tempBuf, 100);
    
  if (length) {
    for (int i = 0; i < length; ++i) {
      // 这段这么写真的好吗
      if (isStart) {
        rxBuf[rxBufPtr++] = tempBuf[i];
        if (rxBuf[rxBufPtr-2] == 0x0d && rxBuf[rxBufPtr-1] == 0x0a) {
          Decode(rxBuf, gb, p1, p2);
          #ifdef __DEBUG_2__
          printf("Decode: ");
          for (int j = 0; j < rxBufPtr; ++j)
            printf("%x ", rxBuf[j]);
          printf("\r\n");
          #endif
          memset(rxBuf, 0, 100);
          rxBufPtr = 0;
        } else if (rxBufPtr == 128) {
          memset(rxBuf, 0, 100);
          isStart = 0;
        }
      } else {
        if (i != length-1 && tempBuf[i] == 0x0d && tempBuf[i+1] == 0x0a) {
          rxBufPtr = 0;
          isStart = 1;
          i += 1;
        }
      }
    }
  } else {
  }
}

void EdcDispGlobalInfo(EDC21Global_InstType * g) {
  printf("%s:\t%d\t%d\t(%d, %d)\t(%d, %d)\t(%d, %d)\r\n",
    g->name, g->time, g->status, g->person[0].x, g->person[0].y, g->person[1].x, g->person[1].y, g->ball.x, g->ball.y);
}

void EdcDispPlayerInfo(EDC21Player_InstType * p) {
  printf("%s:\t%d\t(%d, %d)\t%d\r\n",
    p->name, p->isInLaby, p->pos.x, p->pos.y, p->score);
}
