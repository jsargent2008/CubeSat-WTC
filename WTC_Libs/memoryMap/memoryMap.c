/*
 * memoryMap.c
 *
 *  Created on: Apr 25, 2018
 *      Author: Administrator
 */

#include <mygpio/mygpio.h>
#include "memoryMap/memoryMap.h"

#define GPIO_FLASH_BASEADDR		((uint32_t)0x08080000)

uint8_t gpioAllDump() {

	uint32_t address = GPIO_FLASH_BASEADDR;
	GPIO_TypeDef * ports[] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE };
	uint8_t state;

	for (int port = 0; port < 5; port++) {

		address += port * (sizeof(uint16_t));
		uint16_t data = 0;
		for (int pin = 15; pin >= 0; pin--) {

			state = HAL_GPIO_ReadPin(ports[port], (uint16_t) 1 << pin);
			if (state != GPIO_PIN_RESET) {
				state = 1;
				data |= state;
			} else
				state = 0;

			data = data << 1;
		}

//		the address used is not valid. Please revise.
		if (HAL_FLASHEx_DATAEEPROM_Unlock() == HAL_OK) {
			HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_HALFWORD, address, data);
			//uint32_t data = *(uint32_t *) address; //Read: Cast the address as a uint32_t pointer and dereference it
			HAL_FLASHEx_DATAEEPROM_Lock(); //Lock when done? (Not sure if necessary)
		}
		else
			return 0;
	}

	return 1;
}

uint8_t gpioPortDump(char port) {

	uint32_t address = GPIO_FLASH_BASEADDR;
	GPIO_TypeDef * ports[] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE };
	uint8_t state;

	switch (port) {
	case 'A':
		address += 0 * (sizeof(uint16_t));
		break;
	case 'B':
		address += 1 * (sizeof(uint16_t));
		break;
	case 'C':
		address += 2 * (sizeof(uint16_t));
		break;
	case 'D':
		address += 3 * (sizeof(uint16_t));
		break;
	case 'E':
		address += 4 * (sizeof(uint16_t));
		break;
	default:
		return 0;
		break;
	}

	uint16_t data = 0;
	for (int pin = 15; pin >= 0; pin--) {
		state = HAL_GPIO_ReadPin(ports[port-'A'], (uint16_t) 1 << pin);
		if (state != GPIO_PIN_RESET) {
			state = 1;
			data |= state;
		} else
			state = 0;

		data = data << 1;
	}

//		the address used is not valid. Please revise.
	if (HAL_FLASHEx_DATAEEPROM_Unlock() == HAL_OK) {
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_HALFWORD, address, data);
		//uint32_t data = *(uint32_t *) address; //Read: Cast the address as a uint32_t pointer and dereference it
		HAL_FLASHEx_DATAEEPROM_Lock(); //Lock when done? (Not sure if necessary)
	}
	else
		return 0;

	return 1;
}

uint32_t gpioStatusRetrieve(char port) {

	uint32_t address = GPIO_FLASH_BASEADDR;
	uint32_t data = 0;

	switch (port) {
	case 'A':
		address += 0 * (sizeof(uint16_t));
		break;
	case 'B':
		address += 1 * (sizeof(uint16_t));
		break;
	case 'C':
		address += 2 * (sizeof(uint16_t));
		break;
	case 'D':
		address += 3 * (sizeof(uint16_t));
		break;
	case 'E':
		address += 4 * (sizeof(uint16_t));
		break;
	default:
		return 0;
		break;
	}

	if (HAL_FLASHEx_DATAEEPROM_Unlock() == HAL_OK) {
		data = *(uint32_t *) address; //Read: Cast the address as a uint32_t pointer and dereference it
		HAL_FLASHEx_DATAEEPROM_Lock(); //Lock when done? (Not sure if necessary)
	}
	return data;
}
