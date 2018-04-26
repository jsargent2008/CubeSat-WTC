/*
 * memoryMap.c
 *
 *  Created on: Apr 25, 2018
 *      Author: Administrator
 */

#include "gpio/gpio.h"
#include "memoryMap/memoryMap.h"

#define GPIO_FLASH_BASEADDR		((uint32_t)0x80080000)

void gpioDump() {

	int32_t address = GPIO_FLASH_BASEADDR;
	GPIO_TypeDef * ports[] = { GPIOA, GPIOB, GPIOC, GPIOD, GPIOE };
	uint8_t state;
	uint8_t status = 0;

	for (int port = 0; port < 5; port++) {

		address += port * (sizeof(uint16_t));
		uint16_t data = 0;
		for (int pin = 15; pin >= 0; pin++) {
			state = HAL_GPIO_ReadPin(ports[port], (uint16_t) 1 << pin);
			if (state != GPIO_PIN_RESET) {
				state = 1;
				data |= state;
			} else
				state = 0;

			data = data << 1;
		}

		if (HAL_FLASHEx_DATAEEPROM_Unlock() == HAL_OK) {
			HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_HALFWORD, baseAdr, data);
			uint32_t data = *(uint32_t *) address; //Read: Cast the address as a uint32_t pointer and dereference it
			HAL_FLASHEx_DATAEEPROM_Lock(); //Lock when done? (Not sure if necessary)
		}
	}
}

uint32_t gpioStatusRetrieve(GPIO_TypeDef *port) {

	int32_t address = GPIO_FLASH_BASEADDR;
	switch (port) {
	case GPIOA:
		address += 0 * (sizeof(uint16_t));
		break;
	case GPIOB:
		address += 1 * (sizeof(uint16_t));
		break;
	case GPIOC:
		address += 2 * (sizeof(uint16_t));
		break;
	case GPIOD:
		address += 3 * (sizeof(uint16_t));
		break;
	case GPIOE:
		address += 4 * (sizeof(uint16_t));
		break;
	default:
		return 0;
		break;
	}

	return *(uint32_t *) address;
}

