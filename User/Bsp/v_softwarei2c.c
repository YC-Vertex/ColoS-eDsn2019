#include "v_softwarei2c.h"

// periph layer

void SDA_OUT() {
  HAL_GPIO_DeInit(GPIOA, SDA_Pin);
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  HAL_GPIO_WritePin(GPIOx, SDA_Pin, GPIO_PIN_RESET);
  
  GPIO_InitStruct.Pin = SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
  
  DelayUs(2);
}

void SDA_IN() {
  HAL_GPIO_DeInit(GPIOA, SDA_Pin);
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
  
  DelayUs(2);
}

void SDA(GPIO_PinState ps) {
  HAL_GPIO_WritePin(GPIOx, SDA_Pin, ps);
}

void SCL(GPIO_PinState ps) {
  HAL_GPIO_WritePin(GPIOx, SCL_Pin, ps);
}

GPIO_PinState SDA_DATA() {
  return HAL_GPIO_ReadPin(GPIOx, SDA_Pin);
}

// basic i2c layer

void IIC_Start() {
  SDA_OUT();
  SDA(HIGH);
  SCL(HIGH);
  DelayUs(5);
    
  SDA(LOW);
  DelayUs(5);
  SCL(LOW);
}

void IIC_Stop() {
  SDA_OUT();
  SDA(LOW);
  SCL(LOW);
  DelayUs(5);

  SCL(HIGH);
  DelayUs(5);
  SDA(HIGH);
}

bool IIC_Wait_Ack() {
  unsigned char ucErrTime = 0;
    
  SDA_IN();
  SCL(HIGH);
  DelayUs(2); 	
    
  while (SDA_DATA()) {
    ucErrTime++;
    if (ucErrTime > 250) {
        SDA_OUT();
        IIC_Stop();
      return false;
    }
  }
  SCL(LOW);
  SDA_OUT();
  return true;  
}

void IIC_Ack() {
  SCL(LOW);
  SDA_OUT();
  SDA(LOW);
  DelayUs(2);
  SCL(HIGH);
  DelayUs(2);
  SCL(LOW);
}

void IIC_NAck() {
  SCL(LOW);
  SDA_OUT();
  SDA(HIGH);
  DelayUs(2);
  SCL(HIGH);
  DelayUs(2);
  SCL(LOW);
}
 
void IIC_Send_Byte(uint8_t txd) {
  SDA_OUT();
  SCL(LOW);

  for (int t = 0; t < 8; t++) {
    SDA((txd & 0x80) >> 7);
    txd <<= 1;
    DelayUs(2);
        
    SCL(HIGH);
    DelayUs(2);
    
    SCL(LOW);
    DelayUs(2);
  }	 
} 
 
uint8_t IIC_Read_Byte() {
  unsigned char rxd = 0;
  SDA_IN();
    
  for (int i = 0; i < 8; i++) {
    SCL(LOW);
    DelayUs(2);
    
    SCL(HIGH);
    rxd = (rxd << 1) | SDA_DATA();
    DelayUs(2);
  }
    
  return rxd;
}

// i2c register control layer

bool I2cWriteRegister(uint8_t devaddr, uint8_t addr, uint8_t data) {
  IIC_Start();
  IIC_Send_Byte((devaddr << 1) & 0xfe); // write
  if (!IIC_Wait_Ack()) {
    return false;
  }
  IIC_Send_Byte(addr);
  if (!IIC_Wait_Ack()) {
    return false;
  }
  IIC_Send_Byte(data);
  if (!IIC_Wait_Ack()) {
    return false;
  }
  IIC_Stop();
  
  return true;
}

uint8_t I2cReadRegister(uint8_t devaddr, uint8_t addr) {
  uint8_t data;
  
  IIC_Start();
  IIC_Send_Byte((devaddr << 1) & 0xfe); // write
  if (!IIC_Wait_Ack()) {
    return 0;
  }
  IIC_Send_Byte(addr);
  if (!IIC_Wait_Ack()) {
    return 0;
  }
  
  IIC_Start();
  IIC_Send_Byte((devaddr << 1) | 0x01); // read
  if (!IIC_Wait_Ack()) {
    return 0;
  }
  data = IIC_Read_Byte();
  IIC_NAck();
  IIC_Stop();
  
  return data;
}
