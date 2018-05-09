/*
 * gpio.c
 *
 *  Created on: Apr 7, 2018
 *      Author: Administrator
 */

#include "mygpio/mygpio.h"



void writeDPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
	HAL_GPIO_WritePin(GPIOx,GPIO_Pin,PinState);
}

int readDPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	return HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

