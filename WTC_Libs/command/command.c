/*
 * command.c
 *
 *  Created on: Apr 8, 2018
 *      Author: Administrator
 */

#include "command.h"

//		digital write
//if (strcmp((char *) aRxBuffer, "dw") == 0) {
void dw(UART_HandleTypeDef *huart){
	uint8_t aRxBuffer[20] = "";
	char* prompt; //used for TX line

	putS(&huart,"dw");
	uint8_t flag = 0;
	GPIO_TypeDef* port;
	uint16_t pin;
	GPIO_PinState state;

	// get port X
	getS(&huart,aRxBuffer, 1);
	switch(aRxBuffer[0]) {
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
		flag = 1;
		break;//continue
	}

	//TX received string.
	putS(&huart,aRxBuffer);

	// get pin XX
	getS(&huart,aRxBuffer, 2);

	if(flag == 0)
	{
		pin = atoi(aRxBuffer[0]);
		if(0 <= pin && pin <= 15) {
			pin = 1 << pin;
		} else if(pin == 16) {
			pin = GPIO_PIN_All;
		} else {
			//putS("f2");
			//putS("invalid pin");
			flag = 2;
			//continue;
		}
	}

	//TX received string.
	putS(&huart,aRxBuffer);
	// get state, 1 or 0 X
	getS(&huart,aRxBuffer, 1);
	if(flag == 0)
	{
		state = aRxBuffer[0];
		if(state == '1') {
			state = GPIO_PIN_SET;
		} else if(state == '0') {
			state = GPIO_PIN_RESET;
		} else {
			//putS("f3");
			//putS("invalid state");
			flag = 3;
			//continue;
		}
	}

	//TX received string.
	putS(&huart,aRxBuffer);

	// size of return string should be consistent for every return
	// for easy script writing
	// ex. size of 5
	prompt = mallocCharArray(5);
	prompt[0] = ':';
	if(flag == 0)
	{
		writeDPin(port, pin, state);
		// print "ok" or ":)"
		prompt[1] = 'o';prompt[2] = 'k';prompt[3] = '\n';prompt[4] = '\r';
	}
	else
	{
		//else --> print flags what was caught above.
		prompt[1] = 'f';prompt[2] = (flag+48);prompt[3] = '\n';prompt[4] = '\r';
	}

	putS(&huart, prompt);
	free(prompt);

}
//			digital read
//else if (strcmp((char *) aRxBuffer, "dr") == 0){
void dr(UART_HandleTypeDef *huart){
		uint8_t aRxBuffer[20] = "";
		putS(&huart,"dr");
		int flag = 0;
		GPIO_TypeDef* port;
		uint16_t pin;
		GPIO_PinState state;

		// get port
		getS(&huart,aRxBuffer, 1);
		switch(aRxBuffer[0]) {
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
			putS(&huart,"f1");
			//putS("invalid port");
			flag = 1;
			break;//continue;
		}

		// get pin
		getS(&huart,aRxBuffer, 2);
		if(flag == 0)
		{
			pin = atoi(aRxBuffer[0]);
			if(0 <= pin && pin <= 15)
			{
				pin = 1 << pin;
			}
			else if(pin == 16)
			{
				pin = GPIO_PIN_All;
			}
			else
			{
				putS(&huart,"f2");
				//putS("invalid pin");
				flag = 2;
				//break;//continue;
			}
		}
		// get state, 1 or 0
		getS(&huart,aRxBuffer, 1);
		if(flag == 0)
		{
			state = aRxBuffer[0];
			if(state == '1')
			{
				state = GPIO_PIN_SET;
			}
			else if(state == '0') {
				state = GPIO_PIN_RESET;
			}
			else
			{
				putS(&huart,"f3");
				//putS("invalid state");
				flag = 3;
				//break;//continue;
			}
		}

	}
//			analog write
//else if (strcmp((char *) aRxBuffer, "aw") == 0){
void aw(UART_HandleTypeDef *huart){
	putS(&huart,"aw");
	putS(&huart,"f0");			//putS("not implemented");

}
//			analog read
//else if (strcmp((char *) aRxBuffer, "ar") == 0){
void ar(UART_HandleTypeDef *huart){
	char str[50] = "";
	putS(&huart,"ar");
	float f = 0.0024445;
	sprintf(str, "Val: %f", f);
	HAL_UART_Transmit(&huart, (uint8_t *) str, (uint16_t) sizeof(str), 0xFFFF);
}


