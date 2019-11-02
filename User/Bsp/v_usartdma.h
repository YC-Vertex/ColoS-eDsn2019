#ifndef _V_USART_DMA__H_
#define _V_USART_DMA__H_

#include "main.h"

typedef struct {
  char * name;
  
  UART_HandleTypeDef * usartx;
  DMA_HandleTypeDef * dmax;
  
  uint8_t * rxBuf;
  uint16_t rxBufSize;
  volatile uint8_t rxLen;
  volatile uint8_t rxEndFlag;
} DMA_InstType;

void DmaInit(DMA_InstType * dInst);
_Bool DmaRecv(DMA_InstType * dInst);
void DmaClearBuf(DMA_InstType * dInst);

#endif