#include "main.h"
//#include "stm32l1xx_hal_gpio.h"
#include "stm32l1xx_hal_flash.h"
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


// should remove the following code, because it references "mbed.h"
// check the directory:
// E:\Q-PACE\STM32\STM32_Drivers\en.stm32cubel1\STM32Cube_FW_L1_V1.8.0\Projects\STM32L152D_EVAL\Examples\FLASH
// for a better example on how to write/read to eeprom.
// make sure to add the correct start/stop address in flash (0x08080000 -> ???)

/*
FLASH_Status writeEEPROMByte(uint32_t address, uint8_t data) {
    FLASH_Status status = FLASH_COMPLETE;
    address = address + 0x08080000;
    DATA_EEPROM_Unlock();  //Unprotect the EEPROM to allow writing
    status = DATA_EEPROM_ProgramByte(address, data);
    DATA_EEPROM_Lock();  // Reprotect the EEPROM
    return status;
}

uint8_t readEEPROMByte(uint32_t address) {
    uint8_t tmp = 0;
    address = address + 0x08080000;
    tmp = *(__IO uint32_t*)address;

    return tmp;
}
*/
