/*
 * command.c
 *
 *  Created on: Apr 23, 2018
 *      Author: Clayton White
 */

#include "commands.h"

uint8_t piRequests(UART_HandleTypeDef *huart, char cmd[4]) {

	uint8_t whoseAsking;
	if (huart == &UART_Pi1) {
		whoseAsking = 0;
	} else if (huart == &UART_Pi2) {
		whoseAsking = 1;
	} else {
		return 0;
	}
	//permission check including battery voltage and command
	if (memcmp(cmd, piReq_BUS,4) == 0) {
		//check permission for BUS access
		uint8_t pinState = readDPin(WTC_BUS_Switch_Pi_Select_GPIO_Port,
		WTC_BUS_Switch_Pi_Select_Pin);

		//0 ^ 0 = 0	switch
		//0 ^ 1 = 1	keep
		//1 ^ 1 = 0	switch
		//1 ^ 0 = 1	keep

		if ((pinState ^ whoseAsking) == 0) {
			writeDPin(WTC_BUS_Switch_Pi_Select_GPIO_Port, WTC_BUS_Switch_Pi_Select_Pin,
					GPIO_PIN_SET);
		}
	} else if (memcmp(cmd, piReq_5V,4) == 0) {
		//check permission for 5V access
		writeDPin(_5V_Rail_1_Enable_GPIO_Port, _5V_Rail_1_Enable_Pin, GPIO_PIN_SET);
		writeDPin(_5V_Rail_2_Enable_GPIO_Port, _5V_Rail_2_Enable_Pin, GPIO_PIN_SET);
	} else if (memcmp(cmd, piReq_12V,4) == 0) {
		//check permission for 12V access
		writeDPin(_12V_1_Enable_GPIO_Port, _12V_1_Enable_Pin, GPIO_PIN_SET);
		writeDPin(_12V_2_Enable_GPIO_Port, _12V_2_Enable_Pin, GPIO_PIN_SET);
	} else {

	}
}

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

void testPiComms(uint8_t attempt, UART_HandleTypeDef *huart_CON, UART_HandleTypeDef *huart_Pi) {

	char prompt[10] = { };
	sprintf(prompt, "i %d\r\n", attempt);
	putS(huart_CON, prompt);

	if (readDPin(_5V_Rail_1_Enable_GPIO_Port, _5V_Rail_1_Enable_Pin) != 1
			|| readDPin(_5V_Rail_2_Enable_GPIO_Port, _5V_Rail_2_Enable_Pin) != 1) {

		writeDPin(_5V_Rail_1_Enable_GPIO_Port, _5V_Rail_1_Enable_Pin, GPIO_PIN_SET);
		HAL_Delay(100);
		writeDPin(_5V_Rail_2_Enable_GPIO_Port, _5V_Rail_2_Enable_Pin, GPIO_PIN_SET);
		HAL_Delay(100);
		HAL_Delay(1000);
		putS(huart_CON, "5V ON\r\n");

	} else {
		putS(huart_CON, "5V already on\r\n");
	}

	if (readDPin(Pwr_En_Pi1_GPIO_Port, Pwr_En_Pi1_Pin) != 1) {

		writeDPin(Pwr_En_Pi1_GPIO_Port, Pwr_En_Pi1_Pin, GPIO_PIN_SET);
		HAL_Delay(100);
		putS(huart_CON, "Pi ON\r\n");
		//wait 2 minutes for boot
		waitForBoot(huart_CON);
		//heartbeat pin on
	} else {
		putS(huart_CON, "Pi already on\r\n");
	}

	//REMOVE IF PYTHON UART BOOT CODE HAS BEEN MADE ON THE PI
	//WAIT FOR 'OK'
	char rxBuffer[20] = "";
	putS(huart_CON, "Waiting for initial 'OK' from Pi\r\n");
	while (strcmp(rxBuffer, "OK") != 0) {
		getS(huart_Pi, rxBuffer, 2);
		sprintf(prompt, "%s\r\n", rxBuffer);
		putS(huart_CON, prompt);
	}

	rxBuffer[0] = 0;
	rxBuffer[1] = 0;

	//LED ON
	putS(huart_CON, "Sending 'LED ON' command to Pi\r\n");
	putS(huart_CON, "sending...\r\n");
	writeDPin(Pi_Heartbeat_Pi1_GPIO_Port, Pi_Heartbeat_Pi1_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	//cmd to pi
	putS(huart_Pi, "ON");

	HAL_Delay(100);
	writeDPin(Pi_Heartbeat_Pi1_GPIO_Port, Pi_Heartbeat_Pi1_Pin, GPIO_PIN_RESET);
	putS(huart_CON, "\r\nsent...\r\n");

	//WAIT FOR 'OK'
	//char rxBuffer[20] = "";

	putS(huart_CON, "Waiting for 'OK' from Pi\r\n");
	while (strcmp(rxBuffer, "OK") != 0) {
		getS(huart_Pi, rxBuffer, 2);
		sprintf(prompt, "%s\r\n", rxBuffer);
		putS(huart_CON, prompt);
	}

	rxBuffer[0] = 0;
	rxBuffer[1] = 0;

	HAL_Delay(1000);

	//LED OFF
	putS(huart_CON, "Sending 'LED OFF' command to Pi\r\n");

	putS(huart_CON, "sending...\r\n");
	writeDPin(Pi_Heartbeat_Pi1_GPIO_Port, Pi_Heartbeat_Pi1_Pin, GPIO_PIN_SET);
	HAL_Delay(1000);
	//cmd to pi
	putS(huart_Pi, "OF");

	HAL_Delay(1000);
	writeDPin(Pi_Heartbeat_Pi1_GPIO_Port, Pi_Heartbeat_Pi1_Pin, GPIO_PIN_RESET);
	putS(huart_CON, "\r\nsent...\r\n");

	//WAIT FOR 'OK'
	putS(huart_CON, "Waiting for 'OK' from Pi\r\n");
	while (strcmp(rxBuffer, "OK") != 0) {
		getS(huart_Pi, rxBuffer, 2);
		sprintf(prompt, "%s\r\n", rxBuffer);
		putS(huart_CON, prompt);
	}

	HAL_Delay(200);

	return;
}

/*
 * wait for pi boot
 */
uint8_t waitForBoot(UART_HandleTypeDef *huart) {

	char prompt[100] = { };
	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;
	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);

	uint8_t waitMin = 2;
	uint8_t mins = (stimestructureget.Minutes + waitMin) % 60;
	uint8_t minsActual = stimestructureget.Minutes;

	//wait XX minutes to deploy space craft
	while (mins != minsActual) {
		/* Get the RTC current Time */
		HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
		/* Get the RTC current Date */
		HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);

//			if(minsActual != stimestructureget.Minutes){
		sprintf(prompt, "T-Minus %02d:%02d until Pi COMMS\r", waitMin + (mins - minsActual),
				59 - stimestructureget.Seconds);
		putS(huart, prompt);
//			}
		minsActual = stimestructureget.Minutes;

		HAL_Delay(200);
	}

	sprintf(prompt, "\r\n");
	putS(huart, prompt);

	sprintf(prompt, "----START COMMS WITH PI----\r\n");
	putS(huart, prompt);

	return 0;
}

