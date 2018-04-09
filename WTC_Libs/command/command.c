/*
 * command.c
 *
 *  Created on: Apr 8, 2018
 *      Author: Administrator
 */

#include "command.h"

//		digital write
//if (strcmp((char *) aRxBuffer, "dw") == 0) {
void dw(UART_HandleTypeDef *huart) {
	uint8_t aRxBuffer[20] = "";
	char* prompt; //used for TX line

	putS(huart, "dw");
	uint8_t flag = 0;
	GPIO_TypeDef* port = NULL;
	uint16_t pin = 0;
	GPIO_PinState state = GPIO_PIN_RESET;

	// get port X
	getS(huart, aRxBuffer, 1);
	switch (aRxBuffer[0]) {
	case 'a':
		port = GPIOA;
		break;
	case 'b':
		port = GPIOB;
		break;
	case 'c':
		port = GPIOC;
		break;
	case 'd':
		port = GPIOD;
		break;
	default:
		flag = ERROR_INVALID_PORT;
		break;
	}

	//TX received string.
	putS(huart, (char*) aRxBuffer);

	// get pin XX
	getS(huart, aRxBuffer, 2);

	if (flag == 0) {
		if (isdigit(aRxBuffer[0]) && isdigit(aRxBuffer[1]) ) {
			pin = atoi((char*) aRxBuffer);
			if (0 <= pin && pin <= 15) {
				pin = 1 << pin;
			} else if (pin == 16) {
				pin = GPIO_PIN_All;
			} else {
				flag = ERROR_INVALID_PIN;
			}
		} else {
			flag = ERROR_INVALID_PIN;
		}
	}

	//TX received string.
	putS(huart, (char*) aRxBuffer);

	// get state, 1 or 0 X
	getS(huart, aRxBuffer, 1);
	if (flag == 0) {
		state = aRxBuffer[0];
		if (state == '1') {
			state = GPIO_PIN_SET;
		} else if (state == '0') {
			state = GPIO_PIN_RESET;
		} else {
			//putS("f3");
			//putS("invalid state");
			flag = ERROR_INVALID_STATE;
			//continue;
		}
	}

	//TX received string.
	putS(huart, (char*) aRxBuffer);

	// size of return string should be consistent for every return
	// for easy script writing
	// ex. size of 5
	prompt = mallocCharArray(5);
	prompt[0] = ':';
	if (flag == 0) {

		writeDPin(port, pin, state);

		// print "ok" or ":)"
		sprintf(prompt, ":ok\r\n");
	} else {
		//else --> print flags what was caught above.
		sprintf(prompt, ":f%d\r\n", flag);
	}

	putS(huart, prompt);
	free(prompt);

}

void dr(UART_HandleTypeDef *huart) {
	uint8_t aRxBuffer[20] = "";
	char* prompt; //used for TX line

	putS(huart, "dr");
	uint8_t flag = 0;
	GPIO_TypeDef* port = NULL;
	uint16_t pin = 0;
	GPIO_PinState state = GPIO_PIN_RESET;

	// get port X
	getS(huart, aRxBuffer, 1);
	switch (aRxBuffer[0]) {
	case 'a':
		port = GPIOA;
		break;
	case 'b':
		port = GPIOB;
		break;
	case 'c':
		port = GPIOC;
		break;
	case 'd':
		port = GPIOD;
		break;
	default:
		//putS("f1");
		//putS("invalid port");
		flag = ERROR_INVALID_PORT;
		break;		//continue
	}

	//TX received string.
	putS(huart, (char*) aRxBuffer);

	// get pin XX
	getS(huart, aRxBuffer, 2);

	if (flag == 0) {
		if (isdigit(aRxBuffer[0]) && isdigit(aRxBuffer[1]) ) {
			pin = atoi((char*) aRxBuffer);
			if (0 <= pin && pin <= 15) {
				pin = 1 << pin;
			} else if (pin == 16) {
				pin = GPIO_PIN_All;
			} else {
				flag = ERROR_INVALID_PIN;
			}
		} else {
			flag = ERROR_INVALID_PIN;
		}
	}

	//TX received string.
	putS(huart, (char*) aRxBuffer);

	//read digital pin
	if (flag == 0) {
		state = HAL_GPIO_ReadPin(port, pin);
		if (state != GPIO_PIN_RESET)
			state = 1;
		else
			state = 0;
	}

	// size of return string should be consistent for every return
	// for easy script writing
	// ex. size of 5
	prompt = mallocCharArray(5);
	if (flag == 0) {
		// print "ok" or ":)"
		sprintf(prompt, ":%s\r\n", state ? "hi" : "lo");
	} else {
		//else --> print flags what was caught above.
		sprintf(prompt, ":f%d\r\n", flag);
	}

	putS(huart, prompt);
	free(prompt);
}

//			analog write
//else if (strcmp((char *) aRxBuffer, "aw") == 0){
void aw(UART_HandleTypeDef *huart) {
	putS(huart, "aw");
	putS(huart, "f0");			//putS("not implemented");

}
//			analog read
//else if (strcmp((char *) aRxBuffer, "ar") == 0){
void ar(UART_HandleTypeDef *huart) {
	char str[50] = "";
	putS(huart, "ar");
	float f = 0.0024445;
	sprintf(str, "Val: %f", f);
	HAL_UART_Transmit(huart, (uint8_t *) str, (uint16_t) sizeof(str), 0xFFFF);
}

