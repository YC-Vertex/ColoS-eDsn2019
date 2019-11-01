#ifndef _V_I2C__H_
#define _V_I2C__H_

#include "main.h"

/* ***** USER DEFINITION START ***** */
#define SDA_Pin MPU6050_SDA_Pin
#define SCL_Pin MPU6050_SCL_Pin
#define GPIOx   GPIOA
/* ***** USER DEFINITION END ******* */

#define HIGH    GPIO_PIN_SET
#define LOW     GPIO_PIN_RESET

#define bool    _Bool
#define false   0
#define true    1

void SDA_OUT();
void SDA_IN();
void SDA(GPIO_PinState);
void SCL(GPIO_PinState);
GPIO_PinState SDA_DATA();

void IIC_Start();
void IIC_Stop();
bool IIC_Wait_Ack();
void IIC_Ack();
void IIC_NAck();
void IIC_Send_Byte(uint8_t);
uint8_t IIC_Read_Byte();

bool I2cWriteRegister(uint8_t, uint8_t, uint8_t);
uint8_t I2cReadRegister(uint8_t, uint8_t);

#endif
