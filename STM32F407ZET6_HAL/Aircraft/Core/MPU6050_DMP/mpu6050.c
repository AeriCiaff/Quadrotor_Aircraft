#include "stm32f4xx_hal.h"
#include "i2c.h"
#include "mpu6050.h"
#include <cstdint>


void MPU6050_WriteData(uint8_t reg_addr,uint8_t data ){
    uint8_t w_data = data;
    HAL_I2C_Mem_Write(&MPU_I2C_HANDLE,MPU_WRITE,reg_addr,I2C_MEMADD_SIZE_8BIT,&w_data,1,HAL_MAX_DELAY);
}

void MPU6050_WriteDataLen(uint8_t reg_addr,uint8_t len,uint8_t *data){
    HAL_I2C_Mem_Write(&MPU_I2C_HANDLE,MPU_WRITE,reg_addr,I2C_MEMADD_SIZE_8BIT,data,len,HAL_MAX_DELAY);
}

uint8_t MPU6050_ReadData(uint8_t reg_addr){
    uint8_t r_data;
    r_data = 0;
    HAL_I2C_Mem_Read(&MPU_I2C_HANDLE,MPU_READ,reg_addr,I2C_MEMADD_SIZE_8BIT,&r_data,1,HAL_MAX_DELAY);
    return r_data;
}

uint8_t MPU6050_ReadDataLen(uint8_t reg_addr, uint8_t len, uint8_t *buffer){
    HAL_I2C_Mem_Read(&MPU_I2C_HANDLE,MPU_READ,reg_addr,I2C_MEMADD_SIZE_8BIT,buffer,len,HAL_MAX_DELAY);
    return 0;
}

void MPU6050_SetGyroFsr(uint8_t fsr){
    MPU6050_WriteData(GYRO_CONFIG,fsr<<3);
}

void MPU6050_SetAccFsr(uint8_t fsr){
    MPU6050_WriteData(ACCEL_CONFIG,fsr<<3);
}

void MPU6050_SetRate(uint16_t rate){
    	uint8_t data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(SMPLRT_DIV,data);
 	return MPU_Set_LPF(rate/2);
}

uint8_t MPU6050_Init(void){
    uint8_t res;

    HAL_I2C_Init(&MPU_I2C_HANDLE);
    MPU6050_WriteData(PWR_MGMT_1,0x80);
    HAL_Delay(100);
    MPU6050_WriteData(PWR_MGMT_1,0x00);
    MPU6050_SetGyroFsr(3);
    MPU6050_SetAccFsr(0);
    MPU6050_SetRate(50);
    MPU6050_WriteData(INT_ENABLE,0x00);
    MPU6050_WriteData(USER_CTRL,0x00);
    MPU6050_WriteData(FIFO_EN,0x00);
    MPU6050_WriteData(INT_PIN_CFG,0x80);

    res = MPU6050_ReadData(WHO_AM_I);

    if(res==MPU_ADDR){
        MPU6050_WriteData(PWR_MGMT_1,0x01);
        MPU6050_WriteData(PWR_MGMT_2,0x00);
        MPU6050_SetRate(50);
    }
    else  return 1;
    return 0;
}

short MPU6050_GetTemp(void){
    uint8_t buffer[2];
    short raw;
    float temp;
    MPU6050_ReadDataLen(TEMP_OUT_H,2,buffer);
    raw=((uint16_t)buffer[0]<<8)|buffer[1];  
    temp=36.53+((double)raw)/340;  
    return temp*100;
}

uint8_t MPU6050_GetGyro(short *gx,short *gy,short *gz){
    uint8_t buffer[6],res;
    res = MPU6050_ReadDataLen(GYRO_XOUT_H,6,buffer);
    if(res==0)
	{
		*gx=((uint16_t)buffer[0]<<8)|buffer[1];  
		*gy=((uint16_t)buffer[2]<<8)|buffer[3];  
		*gz=((uint16_t)buffer[4]<<8)|buffer[5];
	} 	
    return res;
}

uint8_t MPU6050_GetAcc(short *ax,short *ay,short *az){
    uint8_t buffer[6],res;
    res = MPU6050_ReadDataLen(ACCEL_XOUT_H,6,buffer);
    if(res==0)
	{
		*ax=((uint16_t)buffer[0]<<8)|buffer[1];  
		*ay=((uint16_t)buffer[2]<<8)|buffer[3];  
		*az=((uint16_t)buffer[4]<<8)|buffer[5];
	} 	
    return res;
}