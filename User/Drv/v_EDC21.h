#ifndef _V_EDC21__H_
#define _V_EDC21__H_

#include "main.h"
#include "v_usartdma.h"

typedef enum {NONE, START, PAUSE, END} Status;

typedef struct {
    uint16_t x;
    uint16_t y;
} XYPos;

typedef struct {
  uint8_t * name;
  
  uint16_t time;
  Status status;
  XYPos person[2];
  XYPos ball;
} EDC21Global_InstType;

typedef struct {
  uint8_t * name;
  
  _Bool isInLaby;
  XYPos pos;
  uint16_t score;
  uint16_t count[3]; // person, catch ball, return ball
  _Bool update[3];
} EDC21Player_InstType;

_Bool Decode(uint8_t * data, EDC21Global_InstType * gb,
    EDC21Player_InstType * p1, EDC21Player_InstType * p2);
void EDC21Handler(DMA_InstType * dma, EDC21Global_InstType * gb,
    EDC21Player_InstType * p1, EDC21Player_InstType * p2);
void EdcDispGlobalInfo(EDC21Global_InstType * g);
void EdcDispPlayerInfo(EDC21Player_InstType * p);

#endif
