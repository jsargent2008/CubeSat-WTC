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


// use for "data2write" pointer in function writeLTC. 1111-1000 sets all V1-V8 pins ready to read. VCC and internal temp.
// see LTC2991 datasheet
#define startAllChannels = 0xf8; //



typedef struct LTC2991 {
	I2C_HandleTypeDef *hi2c;
	uint16_t DevAddress;
	uint8_t returnVal;
} LTC2991;

#endif


//NOTES:

//***
// the argument "size" should account for the MSB and LSB. when reading V1, size should be 2.


//***
// VOLTAGE REGISTER FORMAT
//MSB
//[DV][SIGN][D13][D12][D11][D10][D9][D8]
//LSB
//[D7][D6][D5][D4][D3][D2][D1][D0]
//float result = LTC2991_Single_Ended_Voltage(data);

// TEMPERATURE REGISTER FORMAT
//MSB
//[DV][X][X][D12][D11][D10][D9][D8]
//LSB
//[D7][D6][D5][D4][D3][D2][D1][D0]

