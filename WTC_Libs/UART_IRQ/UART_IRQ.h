#ifndef __UART_IRQ_H__
#define __UART_IRQ_H__

#include "main.h"
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_uart.h"

void UART_IRQ(UART_HandleTypeDef *huart, uint8_t time);

#endif
