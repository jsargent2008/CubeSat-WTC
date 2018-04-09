/*
 * command.h
 *
 *  Created on: Apr 8, 2018
 *      Author: Administrator
 */

#ifndef COMMAND_COMMAND_H_
#define COMMAND_COMMAND_H_

#include "main.h"
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_uart.h"
#include "UART_IRQ/UART_IRQ.h"

void dw(UART_HandleTypeDef *huart);
void dr(UART_HandleTypeDef *huart);
void aw(UART_HandleTypeDef *huart);
void ar(UART_HandleTypeDef *huart);


#endif /* COMMAND_COMMAND_H_ */
