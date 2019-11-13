#include "v_usartdma.h"

void DmaInit(DMA_InstType * dInst) {
  HAL_UART_Receive_DMA(dInst->usartx, dInst->rxBuf, dInst->rxBufSize);
}

// 超出length的部分会被丢失掉
uint16_t DmaRecv(DMA_InstType * dInst, uint8_t * buf, uint16_t length) {
  HAL_UART_DMAStop(dInst->usartx);
  uint16_t counter = __HAL_DMA_GET_COUNTER(dInst->dmax);
  dInst->rxLen = dInst->rxBufSize - counter;
  
  if (dInst->rxLen) {
    length = length < dInst->rxLen ? length : dInst->rxLen;
    for (int i = 0; i < length; ++i) {
      buf[i] = dInst->rxBuf[i];
    }
    DmaClearBuf(dInst);
  }
  else {
    length = 0;
  }
  
  HAL_UART_Receive_DMA(dInst->usartx, dInst->rxBuf, dInst->rxBufSize); // 重新打开dma接收
  return length;
}

void DmaClearBuf(DMA_InstType * dInst) {
  dInst->rxLen = 0;
  memset(dInst->rxBuf, 0, sizeof(uint8_t) * dInst->rxBufSize);
}