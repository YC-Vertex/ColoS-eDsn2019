#include "v_usartdma.h"

void DmaInit(DMA_InstType * dInst) {
  HAL_UART_Receive_DMA(dInst->usartx, dInst->rxBuf, dInst->rxBufSize);
}

_Bool DmaRecv(DMA_InstType * dInst) {
  HAL_UART_DMAStop(dInst->usartx);
  uint16_t counter = __HAL_DMA_GET_COUNTER(dInst->dmax);
  dInst->rxLen = dInst->rxBufSize - counter;
  if (dInst->rxLen) {
    dInst->rxEndFlag = 1;
  }
  HAL_UART_Receive_DMA(dInst->usartx, dInst->rxBuf, dInst->rxBufSize); // 重新打开dma接收
  
  return dInst->rxEndFlag;
}

void DmaClearBuf(DMA_InstType * dInst) {
  dInst->rxLen = 0;
  dInst->rxEndFlag = 0;
  memset(dInst->rxBuf, 0, sizeof(uint8_t) * dInst->rxBufSize);
}