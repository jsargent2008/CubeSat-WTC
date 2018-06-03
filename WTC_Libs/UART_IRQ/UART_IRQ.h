#ifndef __UART_IRQ_H__
#define __UART_IRQ_H__

#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_uart.h"

void UART_IRQ(UART_HandleTypeDef *huart, uint8_t time);
void UART_printSOS(UART_HandleTypeDef *huart, uint32_t time);
void UART_PUT(UART_HandleTypeDef *huart, char *str);

void putS(UART_HandleTypeDef *huart, char* buf);
void getS(UART_HandleTypeDef *huart, char* buf, uint8_t len);
void putB(UART_HandleTypeDef *huart, char* buf, uint16_t len);
void getB(UART_HandleTypeDef *huart, char *buf, uint8_t len);
// char array stuff, useful as supplementary functiosn for
// the uart functions above ^^^
char* mallocCharArray(uint32_t size);
char* appendCharArrays(char* dest, char* src, uint32_t index);
uint32_t arraylength(char* array);
#endif
