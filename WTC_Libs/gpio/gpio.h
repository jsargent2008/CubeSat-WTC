/*
 * gpio.h
 *
 *  Created on: Apr 7, 2018
 *      Author: Administrator
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include "main.h"
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_gpio.h"
#include "stm32l1xx_hal_gpio_ex.h"


void writeDPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
int readDPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);




#endif /* GPIO_GPIO_H_ */
