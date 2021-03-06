/*
 * command.c
 *
 *  Created on: Apr 8, 2018
 *      Author: Administrator
 */

#include "command.h"

// LTC switch function
void ltc(I2C_HandleTypeDef *hi2c, UART_HandleTypeDef *huart) {

	// todo
	// read all channels for 1 ltc device

	putS(huart, "lt");
	char aRxBuffer[20] = "";
	char prompt[20] = "";

	getS(huart, aRxBuffer, 1);

	int8_t nltc = atoi((char *) aRxBuffer);

	//TX received string.
	putS(huart, (char*) aRxBuffer);

	uint8_t addr;

	if (nltc == 0) {
		addr = LTC2991_I2C_ADDRESS_1; //macro
	} else if (nltc == 1) {
		addr = LTC2991_I2C_ADDRESS_2;
	} else if (nltc == 2) {
		addr = LTC2991_I2C_ADDRESS_3;
	} else if (nltc == 3) {
		addr = LTC2991_I2C_ADDRESS_4;
	} else if (nltc == 4) {
		addr = LTC2991_I2C_ADDRESS_5;
	} else if (nltc == 5) {
		addr = LTC2991_I2C_ADDRESS_6;
	} else if (nltc == 6) {
		addr = LTC2991_I2C_ADDRESS_7;
	} else if (nltc == 7) {
		addr = LTC2991_I2C_ADDRESS_8;
	} else {
		sprintf(prompt, "addr wrong\r\n");
		putS(huart, prompt);
		return;
	}

	// get channel X
	getS(huart, aRxBuffer, 1);

	int8_t channel = atoi((char *) aRxBuffer);
	if (!isdigit(aRxBuffer[0]))
		channel = aRxBuffer[0];

	//TX received string.
	putS(huart, (char*) aRxBuffer);

	uint8_t readAll = 0;

	if (1 <= channel && channel <= 8) {
		channel = channel;
	} else if (channel == 'a') { //read all voltages
		readAll = 1;
	} else if (channel == 'v') { //read internal voltages
		channel = 10;
	} else if (channel == 't') { //read internal temperature
		channel = 9;
	} else {
		sprintf(prompt, "channel wrong\r\n");
		putS(huart, prompt);
		return;
	}

	sprintf(prompt,"\r\n");
	putS(huart, prompt);

	LTC2991 *ltc;
	ltc = initLTC2991(hi2c, addr);

	if (readAll == 0) {
		readChannelLTC(ltc, huart, channel);
	} else
		readAllLTC(ltc, huart);

	free(ltc);

}

// ks switch function
void ks(UART_HandleTypeDef *huart) {

	putS(huart, "ks");
	char aRxBuffer[20] = "";
	char prompt[100] = { };

	GPIO_TypeDef* port = NULL;
	uint16_t pin = 0;
	GPIO_PinState state = GPIO_PIN_SET;
	port = GPIOE;

// get kill switch number
	getS(huart, aRxBuffer, 1);

	int8_t ks_pin = atoi((char *) aRxBuffer);

	if (ks_pin == 1) {
		pin = 14;
	} else if (ks_pin == 2) {
		pin = 15;
	} else {
		sprintf(prompt, "denied\r\n");
		putS(huart, prompt);
		return;
	}

	sprintf(prompt, "good bye\r\n");
	putS(huart, prompt);
	writeDPin(port, pin, state);
}

//		digital write
void dw(UART_HandleTypeDef *huart) {

	putS(huart, "dw");
	char aRxBuffer[20] = "";
	char prompt[100] = { };

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
	case 'e':
		port = GPIOE;
		break;
	case 'h':
		port = GPIOH;
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
		if (isdigit(aRxBuffer[0]) && isdigit(aRxBuffer[1])) {
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
// make sure not to access kill switch.
	if (port == GPIOE) {
		if (pin == Kill_Switch_1_Pin || pin == Kill_Switch_2_Pin || pin == GPIO_PIN_All) {
			sprintf(prompt, ":access denied\r\n");
			putS(huart, prompt);
			flag = 4;
			sprintf(prompt, ":f%d\r\n", flag);
			putS(huart, prompt);
			return;
		}
	}

	if (flag == 0) {
		writeDPin(port, pin, state);
		// print "ok" or ":)"
		sprintf(prompt, ":ok\r\n");
	} else {
		//else --> print flags what was caught above.
		sprintf(prompt, ":f%d\r\n", flag);
	}

	putS(huart, prompt);

}

void dr(UART_HandleTypeDef *huart) {

	putS(huart, "dr");
	char aRxBuffer[20] = "";
	char prompt[100] = { };

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
	case 'e':
		port = GPIOE;
		break;
	case 'h':
		port = GPIOH;
		break;
	default:
		//putS("f1");
		//putS("invalid port");
		flag = ERROR_INVALID_PORT;
		break;		//continue
	}

//TX received string.
	putS(huart,aRxBuffer);

// get pin XX
	getS(huart, aRxBuffer, 2);

	if (flag == 0) {
		if (isdigit(aRxBuffer[0]) && isdigit(aRxBuffer[1])) {
			pin = atoi(aRxBuffer);
			if (0 <= pin && pin <= 15) {
				pin = 1 << pin;
			} else if (pin == 16) {
				putS(huart, aRxBuffer);
				drAllport(huart, port);
				//pin = GPIO_PIN_All;
			} else {
				flag = ERROR_INVALID_PIN;
			}
		} else {
			flag = ERROR_INVALID_PIN;
		}
	}

	if (pin != 16) {
		//TX received string.
		putS(huart, aRxBuffer);
	}


	if (flag == 0) {
		//read digital pin
		state = HAL_GPIO_ReadPin(port, pin);

		if (state != GPIO_PIN_RESET)
			state = 1;
		else
			state = 0;
		// print "ok" or ":)"
		sprintf(prompt, ":%s\r\n", state ? "hi" : "lo");
	} else {
		//else --> print flags what was caught above.
		sprintf(prompt, ":f%d\r\n", flag);
	}

	putS(huart, prompt);
}

//			analog write
void aw(UART_HandleTypeDef *huart) {
	putS(huart, "aw");
	putS(huart, "f0");

}

//uint32_t channels =  {
//			analog read
void ar(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc) {
	putS(huart, "ar");
	uint8_t flag = 0;
	char aRxBuffer[20] = "";
	uint8_t baseChannel = ADC_CHANNEL_0;
	uint16_t readChannel = 0;
	char str[50] = "";

// get pin XX
	getS(huart, aRxBuffer, 2);

	if (flag == 0) {
		if (isdigit(aRxBuffer[0]) && isdigit(aRxBuffer[1])) {
			readChannel = atoi((char*) aRxBuffer);
			if (0 <= readChannel && readChannel <= 31) {
				readChannel = baseChannel + readChannel;
			} else if (readChannel == 32) {
				//use flag to prevent reading Channel 32
				//flag = ERROR_SKIP; // currently not used.
				//TX received string.
				putS(huart, (char*) aRxBuffer);

				arAll(huart, hadc);
			} else {
				flag = ERROR_INVALID_PIN;
			}
		} else {
			flag = ERROR_INVALID_PIN;
		}
	}

	if (readChannel != 32) {
		//TX received string.
		putS(huart, (char*) aRxBuffer);
	}
//		sprintf(str, "\r\n" PRINTF_BINARY_PATTERN_INT32  , PRINTF_BYTE_TO_BINARY_INT32(readChannel));
//		HAL_UART_Transmit(huart, (uint8_t *) str, (uint16_t) sizeof(str), 0xFFFF);
//		sprintf(str, "\r\n" PRINTF_BINARY_PATTERN_INT32  , PRINTF_BYTE_TO_BINARY_INT32(ADC_CHANNEL_10));
//		HAL_UART_Transmit(huart, (uint8_t *) str, (uint16_t) sizeof(str), 0xFFFF);
	if (flag == 0) {
		float f = adcReadSingle(hadc, readChannel);
		sprintf(str, ":%02d-%.3f\r\n", readChannel, f);
		putS(huart, str);
	} else {
		sprintf(str, ":f%d\r\n", flag); //decimal
		putS(huart, str);
	}
}

void arAll(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc) {
	char str[50] = "";
	int nADCchannels = 32;

	for (int i = 0; i < nADCchannels; i++) {
		float f = adcReadSingle(hadc, i);

		sprintf(str, ":%02d-%.3f\r\n", i, f); //decimal
		putS(huart, str);
	}
}

void drAllport(UART_HandleTypeDef *huart, GPIO_TypeDef* port) {

	char str[50] = "";
//GPIO_TypeDef* port = NULL;
	GPIO_PinState state = GPIO_PIN_RESET;
	uint8_t i;

	switch ((int) port) {
	case (int) GPIOA:
		i = 'a';  //a
		break;
	case (int) GPIOB:
		i = 'b';  // b
		break;
	case (int) GPIOC:
		i = 'c';  //c
		break;
	case (int) GPIOD:
		i = 'd';  //c
		break;
	default:
		i = '?';
	}

	for (int pin = 0; pin < 16; pin++) {
		state = HAL_GPIO_ReadPin(port, (uint16_t) 1 << pin);
		if (state != GPIO_PIN_RESET)
			state = 1;
		else
			state = 0;
		//prompt, ":%s\r\n", state ? "hi" : "lo");
		sprintf(str, ":port%c_pin%02d-%s\r\n", i, pin, state ? "hi" : "lo");
		putS(huart, str);
	}
}

void tt(UART_HandleTypeDef *huart, UART_HandleTypeDef *hout) {
	putS(huart, "tt");
	uint8_t packet_size = 12;

	char aRxBuffer[20] = "";
	char prompt[20] = {};
	getS(huart, aRxBuffer, packet_size);
	sprintf(prompt, "%s\r\n", aRxBuffer);
	putS(huart,aRxBuffer);

	HAL_Delay(20);

	getS(huart, aRxBuffer, packet_size);
	sprintf(prompt, "%s\r\n", aRxBuffer);
	putS(huart,aRxBuffer);
}
