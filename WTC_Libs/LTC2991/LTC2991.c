#include "LTC2991.h"
#define LTCrocks TRUE;

// Calibration Variables
//! Typical single-ended LSB weight in volts
const float LTC2991_SINGLE_ENDED_lsb = 3.05176E-04;
//! Typical differential LSB weight in volts
const float LTC2991_DIFFERENTIAL_lsb = 1.90735E-05;
//! Typical VCC LSB weight in volts
const float LTC2991_VCC_lsb = 3.05176E-04;
//! Typical temperature LSB weight in degrees Celsius (and Kelvin).
//! Used for internal temperature as well as remote diode temperature measurements.
const float LTC2991_TEMPERATURE_lsb = 0.0625;
//! Typical remote diode LSB weight in volts.
//! Used to readback diode voltage when in temperature measurement mode.
const float LTC2991_DIODE_VOLTAGE_lsb = 3.815E-05;

/**
 * @brief  Write an amount of data in blocking mode to a specific memory address
 * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
 * @retval HAL status
 */
uint8_t CheckDevAddress(uint16_t DevAddress) {
	if (DevAddress != 0x90 || DevAddress != 0x92 || DevAddress != 0x94
			|| DevAddress != 0x96 || DevAddress != 0x98 || DevAddress != 0x9A
			|| DevAddress != 0x9C || DevAddress != 0x9E) {
		return 1;
	} else {
		return 0;
	}
}

/**
 * @brief  ?
 * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
 * @param  DevAddress ?
 * @param  MemAddress ?
 * @param  data2write ?
 * @retval uint8_t ?
 */


LTC2991 *initLTC(I2C_HandleTypeDef *hi2c, uint16_t DevAddress,uint8_t *data2write) {
	LTC2991 *myLTC = malloc(sizeof(LTC2991));
	if (myLTC != NULL) {
		myLTC->hi2c = hi2c;
		myLTC->DevAddress = DevAddress;

//		uint8_t data2write = 0xF8; //Enable reading all voltages V1-V8 & enable internal Temperature and Vcc
		myLTC->returnVal = WriteLTC(hi2c, DevAddress, 0x01, data2write);
	}

	return myLTC;
}

uint8_t WriteLTC(I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
		uint16_t MemAddress, uint8_t *data2write) {

		if (CheckDevAddress(DevAddress)) {
			//check memory address to write to, return if the address is incorrect.
			if (MemAddress != 0x01 //Channel Enable-Status, Trigger
			|| MemAddress != 0x06 //V1, V2, V3 and V4 Control Register
			|| MemAddress != 0x07 //V5, V6, V7 and V8 Control Register
			|| MemAddress != 0x08 //PWM Threshold and Tinternal Control Register
			|| MemAddress != 0x09) { ////PWM Threshold
			//Invalid memory addresses to write to
			return 0;
		}

		HAL_Delay(100);
		//HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
		HAL_I2C_Mem_Write(hi2c, DevAddress, MemAddress, I2C_MEMADD_SIZE_8BIT,
				data2write, 1, 1000); //Write data2write in MemAddress of DevAddress

		//*************Example*************
		//uint8_t data2write = 0xF8; //Enable reading all voltages V1-V8 & enable internal Temperature and Vcc
		//HAL_I2C_Mem_Write(hi2c, 0x90, 0x01, I2C_MEMADD_SIZE_8BIT, &data2write, 1, 1000); //enable all channels (V1-V8) status register 0x01 on LTC2991 Device address 0x90
	}
	else
	{
		return 0;
	}

	return 0;
}

/*
uint8_t ReadLTC(LTC2991 ltc, int16_t StartMemAddress, uint8_t *pData01, uint16_t Size) {
	ReadLTC(ltc->hi2c, ltc->DevAddress, pData01, Size);
}

*/

/**
 * @brief  ?
 * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
 * @param  DevAddress ?
 * @param  StartMemAddress ?
 * @param  pData01 ?
 * @param  Size ?
 * @retval uint8_t ?
 */
uint8_t ReadLTC(I2C_HandleTypeDef *hi2c, uint16_t DevAddress,
		uint16_t StartMemAddress, uint8_t *pData01, uint16_t Size) {

	if (CheckDevAddress(DevAddress)) {
		HAL_Delay(100);
		//HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
		//HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)

		HAL_I2C_Mem_Read(hi2c, DevAddress, StartMemAddress,
				I2C_MEMADD_SIZE_16BIT, pData01, Size, 1000);

		// possible to include feedback status bit from I2C mem read function as
		// a return for READLTC

		//*************Example*************
		//HAL_I2C_Mem_Read(hi2c, 0x90, 0x01, I2C_MEMADD_SIZE_8BIT, pData01, 1, 1000); //status of channels
		//HAL_I2C_Mem_Read(hi2c, 0x90, 0x0A, I2C_MEMADD_SIZE_8BIT, pData01, 2, 1000); //Read MSB (0x0A) and LSB (0x0B) of V1
		//HAL_I2C_Mem_Read(hi2c, 0x90, 0x0A, I2C_MEMADD_SIZE_8BIT, pData01, 16, 1000); //Read MSB and LSB of V1-V8 (0x0A to 0x19)
	}

	else
	{
		return 0;
	}

	// consider changing return statement to account if the "if/else" statement was
	// implemented.

	return 0;
}

/**
 * @brief  ?
 * @param  ADC_Reg_Val ?
 * @retval float ?
 */
float LTC2991_Vcc(uint16_t ADC_Reg_Val) {
	float Vcc;
	int16_t sign = 1;
	if (ADC_Reg_Val >> 14) {
		ADC_Reg_Val = (ADC_Reg_Val ^ 0x7FFF) + 1; //! 1) Converts two's complement to binary
		sign = -1;
	}

	Vcc = (((float) ADC_Reg_Val) * LTC2991_VCC_lsb * sign) + 2.5; //! 2) Convert code to Vcc Voltage from single-ended lsb
	return (Vcc);
}

/**
 * @brief  ?
 * @param  ADC_Reg_Val ?
 * @retval float ?
 */
float LTC2991_IntTemp(uint16_t ADC_Reg_Val) {
	float IntTemp;
	ADC_Reg_Val = (ADC_Reg_Val & 0x1FFF);            //! 1) Removes first 3 bits

	if (ADC_Reg_Val >> 12) {
		ADC_Reg_Val = (ADC_Reg_Val | 0xE000);            //! Sign extend Celsius
	}

	IntTemp = ((float) ADC_Reg_Val) * LTC2991_TEMPERATURE_lsb; //! 2) Converts code to temperature from temperature lsb
	return (IntTemp);
}

/**
 * @brief  ?
 * @param  ADC_Reg_Val ?
 * @retval float ?
 */
float LTC2991_Single_Ended_Voltage(uint16_t ADC_Reg_Val) {
	float voltage;
	int16_t sign = 1;

	// check table 9 of LTC2991 datasheet
	// d0 -d13 are used.
	// the remaining bits (sign and DV*) are not used

	if (ADC_Reg_Val >> 14) {
		ADC_Reg_Val = (ADC_Reg_Val ^ 0x7FFF) + 1; //! 1) Converts two's complement to binary
		sign = -1;
	}
	ADC_Reg_Val = (ADC_Reg_Val & 0x3FFF);
	voltage = ((float) ADC_Reg_Val) * LTC2991_SINGLE_ENDED_lsb * sign; //! 2) Convert code to voltage from lsb

	return (voltage);
}

/**
 * @brief  ?
 * @param  ADC_Reg_Val ?
 * @retval float ?
 */
float LTC2991_Diode_Voltage(uint16_t ADC_Reg_Val) {
	float voltage;
	ADC_Reg_Val = (ADC_Reg_Val & 0x1FFF);            //! 1) Removes first 3 bits
	voltage = ((float) ADC_Reg_Val) * LTC2991_DIODE_VOLTAGE_lsb; //! 2) Convert code to voltage from diode voltage lsb
	return (voltage);
}
