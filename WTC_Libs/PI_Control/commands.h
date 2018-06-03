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
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_uart.h"
#include "usart.h"
#include "rtc.h"
#include "gpio.h"
#include <myprintf/myprintf.h>
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

//pi  request commands
#define piReq_5V "__5V" "--> '_','_','5','V' "
#define piReq_12V "_12V"
#define piReq_BUS "_BUS"

uint8_t piRequests(UART_HandleTypeDef *huart, char cmd[3]);
uint8_t initHandShake(UART_HandleTypeDef *huart);
uint8_t sendCommand(UART_HandleTypeDef *huart, uint8_t command);
uint8_t piNum(UART_HandleTypeDef *huart);

uint8_t waitForBoot(UART_HandleTypeDef *huart);
void testPiComms(uint8_t attempt, UART_HandleTypeDef *huart_CON, UART_HandleTypeDef *huart_Pi);

#endif /* PI_CONTROL_COMMANDS_H_ */
