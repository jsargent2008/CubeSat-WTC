/*
 * commands.h
 *
 * Defines the commands used for bidirectional UART communication for the Raspberry PI.
 *
 *  Created on: April 23, 2018
 *      Author: Clayton White
 */

#ifndef PI_CONTROL_COMMANDS_H_
#define PI_CONTROL_COMMANDS_H_

#include "main.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <myprintf/myprintf.h>
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_uart.h"
#include "usart.h"
#include "UART_IRQ/UART_IRQ.h"

#define ACK 			"OK"
#define OK				"OK"
#define NO				"NO"
#define SHUTDOWN		"SD"
#define SHUTDOWN_PRO 	"SP"
#define REBOOT			"RE"
#define SEND_FILE 		"SF"
#define SEND_PACKETS 	"AP"
#define PING 			"HI"
#define STATUS			"ST"
#define CHECK_SIBLING 	"CS"
#define PIPE_COMMAND 	"PC"
#define UART_CHECK		"UC"

uint8_t initHandShake(UART_HandleTypeDef *huart);
uint8_t sendCommand(UART_HandleTypeDef *huart, uint8_t command);
uint8_t piNum(UART_HandleTypeDef *huart);

#endif /* PI_CONTROL_COMMANDS_H_ */
