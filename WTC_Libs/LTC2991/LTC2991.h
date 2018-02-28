#ifndef __LTC2991_H__
#define __LTC2991_H__

#include "main.h"
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_i2c.h"

uint8_t CheckDevAddress(uint16_t DevAddress);
uint8_t WriteLTC(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint8_t *data2write);
uint8_t ReadLTC(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t StartMemAddress, uint8_t *pData01, uint16_t Size);

float LTC2991_Vcc(uint16_t ADC_Reg_Val);
float LTC2991_IntTemp(uint16_t ADC_Reg_Val);
float LTC2991_Single_Ended_Voltage(uint16_t ADC_Reg_Val);
float LTC2991_Diode_Voltage(uint16_t ADC_Reg_Val);
#endif
