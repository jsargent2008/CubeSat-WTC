/*
 * command.c
 *
 *  Created on: Apr 23, 2018
 *      Author: Clayton White
 */

#include "commands.h"

// sends "OK" to Pi # x and confirms whether "OK" was received back
uint8_t initHandShake(UART_HandleTypeDef *huart) {

	//uint8_t pi = piNum(huart);

	putS(huart, OK);
	//wait for response back from pi

	HAL_Delay(1000);
	// or use DMA interrupt

	char aRxBuffer[20] = "";
	getS(huart, aRxBuffer, 1);

	if (strcmp(OK, aRxBuffer) == 0) {
		return 0;
	} else
		return 1;
}

uint8_t sendCommand(UART_HandleTypeDef *huart, uint8_t command) {

	uint8_t pi = piNum(huart);
	return pi;
}

uint8_t piNum(UART_HandleTypeDef *huart) {
	uint8_t pi = 0;
	if (huart == &UART_Pi1) {
		pi = 1;
	} else if (huart == &UART_Pi2) {
		pi = 2;
	}

	return pi;
}

