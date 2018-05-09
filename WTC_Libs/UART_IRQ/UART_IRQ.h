#ifndef __UART_IRQ_H__
#define __UART_IRQ_H__

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "usart.h"

void UART_IRQ(UART_HandleTypeDef *huart, uint8_t time);
void UART_printSOS(UART_HandleTypeDef *huart, uint32_t time);
void UART_PUT(UART_HandleTypeDef *huart, char *str);

void putS(UART_HandleTypeDef *huart, char* buf);
void getS(UART_HandleTypeDef *huart, char* buf, uint8_t len);

// char array stuff, useful as supplementary functiosn for
// the uart functions above ^^^
char* mallocCharArray(uint32_t size);
char* appendCharArrays(char* dest, char* src, uint32_t index);
uint32_t arraylength(char* array);

#if defined(STM32L0) // maps UART_HandleTypeDef->State to ->gState
#define State gState
#endif

#include "UART_IRQ.c"

#undef State

#endif
