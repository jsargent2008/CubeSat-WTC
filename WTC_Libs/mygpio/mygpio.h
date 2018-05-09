/*
 * gpio.h
 *
 *  Created on: Apr 7, 2018
 *      Author: Administrator
 */

#ifndef MYGPIO_MYGPIO_H_
#define MYGPIO_MYGPIO_H_

#include "main.h"
#include "gpio.h"



void writeDPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
int readDPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);



#include "mygpio.c"
#endif /* MYGPIO_MYGPIO_H_ */
