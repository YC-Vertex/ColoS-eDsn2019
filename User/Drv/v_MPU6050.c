#include "v_MPU6050.h"

void MpuInit() {
    I2cWriteRegister(DEV_ADDR, PWR_MGMT_1, 0x00);
    I2cWriteRegister(DEV_ADDR, SMPLRT_DIV, 0x00);
    I2cWriteRegister(DEV_ADDR, CONFIG, 0x01);
    I2cWriteRegister(DEV_ADDR, GYRO_CONFIG, 0x18);
    I2cWriteRegister(DEV_ADDR, ACCEL_CONFIG, 0x01);
}

uint16_t MpuGetRawData(uint8_t reg_addr) {
    uint8_t H, L;
    H = I2cReadRegister(DEV_ADDR, reg_addr);
    L = I2cReadRegister(DEV_ADDR, reg_addr + 1);
    return (H << 8) + L;
}

void MpuGetAngle(MPU6050_InstType * mpuInst, float * buf) {
  buf[0] = mpuInst->xAngle;
  buf[1] = mpuInst->yAngle;
  buf[2] = mpuInst->zAngle;
}

float MpuGetXAngle(MPU6050_InstType * mpuInst) {
  return mpuInst->xAngle;
}

float MpuGetYAngle(MPU6050_InstType * mpuInst) {
  return mpuInst->yAngle;
}

float MpuGetZAngle(MPU6050_InstType * mpuInst) {
  return mpuInst->zAngle;
}



void MpuDataHandler(MPU6050_InstType * mInst, uint32_t clkFreq) {
}
  