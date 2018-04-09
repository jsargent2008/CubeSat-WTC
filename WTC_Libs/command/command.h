/*
 * command.h
 *
 *  Created on: Apr 8, 2018
 *      Author: Administrator
 */

#ifndef COMMAND_COMMAND_H_
#define COMMAND_COMMAND_H_

#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_uart.h"
#include "UART_IRQ/UART_IRQ.h"
#include "gpio/gpio.h"
#include "adc/adc.h"
#include "PRINTF/printf.h"

#define ERROR_INVALID_PORT 1
#define ERROR_INVALID_PIN 2
#define ERROR_INVALID_STATE 3
#define ERROR_SKIP 4			//example use. cmd "ar32" will print channel 32 after it complete the arALL call
								// channel 32 is invalid. memory leak.
void dw(UART_HandleTypeDef *huart);
// void dwAllport(UART_HandleTypeDef *huart, GPIO_TypeDef* port);  this function can be implemented by using the pin value 16
void dr(UART_HandleTypeDef *huart);
void drAllport(UART_HandleTypeDef *huart, GPIO_TypeDef* port);
void aw(UART_HandleTypeDef *huart);
void ar(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc);
void arAll(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc);

#endif /* COMMAND_COMMAND_H_ */
