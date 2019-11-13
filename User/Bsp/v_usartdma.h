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
} DMA_InstType;

void DmaInit(DMA_InstType * dInst);
uint16_t DmaRecv(DMA_InstType * dInst, uint8_t * buf, uint16_t length);
void DmaClearBuf(DMA_InstType * dInst);

#endif