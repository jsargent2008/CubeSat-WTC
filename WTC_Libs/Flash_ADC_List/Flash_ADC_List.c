#include "main.h"
//#include "stm32l1xx_hal_gpio.h"
//#include "stm32l1xx_hal_flash.h"
//#include "stm32l1xx_hal_flash_ex.h"

// LTC2991 code
#include "LTC2991/LTC2991.h"

// 	3-1-2018
//	Theodore Cox
// 	source file to send ADC data to flash memory
//	ADC data includes values from WTC GPIO and Avionics stack LTC2991 ICs.
//	The ADC values will be stored in a contiguous list in FLASH memory.

/*
 * 	readADClist
 * 	return type: ?
 */
void readADClist() {

	//	3-2-18
	//	find ADClist in flash memory
	//	ADCLIST should be contiguous block of memory
	//	This should output the values of the ADC list an array.

}

/*
 * 	writetoADClist
 *	return type: ?
 */
void writetoADClist() {

	//	3-2-18
	//	loop through two modules to gather all ADC values
	//	module 1: 	WTC GPIO ADC pins
	//	module 2:	LTC2991 Values (i2c)

	//	ADC list should start at flash memory 0x????? (non-volatile)
	//

}

