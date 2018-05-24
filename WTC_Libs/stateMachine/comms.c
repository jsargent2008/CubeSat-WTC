/*
 * comms.c
 *
 *  Created on: May 22, 2018
 *      Author: Administrator
 */

#include "comms.h"

/*
 * IMPORTANT!
 * SET TX PINS to a PULL DOWN UNTIL SOMETHING HAS BEEN RECIEVED BY
 * GROUND. SETTING THE PIN TO UART MAY DO THIS AUTOMATICALLY, CHECK
 * WITH DMM THAT THE TX VOLTAGE IS LOW WHILE NOT TRANSIMITTING.
 * THIS IS INCASE ONE OF THE TRANSIFERS IS ACTING WERID, (We cannot disable the transceiver.
 * NO NEED TO DISABLE OR ENABLE 70cm PINS, the are floating.
 */

CommsRxPacketStruct my_commsRxPacketStruct;
CommsRxPacketStruct *commsRx = &my_commsRxPacketStruct;

CommsTxPacketStruct my_commsTxPacketStruct;
CommsTxPacketStruct *commsTx = &my_commsTxPacketStruct;

void commsLoop(uint8_t* buffer) {

	//Check for CWB beacon
	//if DMA interrupt on 70cm UART PORT
	/*
	 * step 1: receive data in buffer from ground
	 * step 2: direct to hello procedure
	 * step 3:
	 */
}

/*
 * call this function if ground is trying to communicate with the WTC
 *
 */
void helloGround(uint8_t* buffer) {
	char prompt[100] = { };
	//change debug_uart port to 70cm in use.  primary or secondary
	sprintf(prompt, "Hello, I am WTC");
	putS(&DEBUG_UART, prompt);

}
void commsToGround(uint8_t* buffer) {
	//Make sure transmission window does not exceed 10 minutes.
	char prompt[100] = { };
	uint8_t maxTransmissionTime = 10;

	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;
	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);

	uint8_t timeWindow_min = (stimestructureget.Minutes + maxTransmissionTime) % 60;
	sprintf(prompt, "Transmission to ground starting now.");

	putS(&DEBUG_UART, prompt);
	sprintf(prompt, "Time Stamp:\r\n\tDay%d:%d:%d\r\n\ttime%d:%d:%d", sdatestructureget.Date,
			sdatestructureget.Month, sdatestructureget.Year, (uint8_t) stimestructureget.Hours,
			(uint8_t) stimestructureget.Minutes, (uint8_t) stimestructureget.Seconds);
	putS(&DEBUG_UART, prompt);

	//wait XX minutes to STOP COMMS to GROUND
	while (timeWindow_min != stimestructureget.Minutes) {
		/* Get the RTC current Time */
		HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
		/* Get the RTC current Date */
		HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);

		//TRANSMIT STUFF TO GROUND.
		//BREAK IF....?
		HAL_Delay(200);
	}

}

void commsFromGround(uint8_t* buffer) {
	/*
	 * parse through the first byte of the 128-byte packet
	 * ...pass buffer accordingly
	 */
	char prompt[100] = { };
	commsRx->designator = buffer[1];

	switch (commsRxPacketStruct->designator) {
	case (designatorWTC):

		sprintf(prompt, "commsToWTC");
		putS(&DEBUG_UART, prompt);

		commsToWTC(buffer);
		//go to WTC transmission code
		break;
	case (designatorPi1):

		sprintf(prompt, "commsToPi1");
		putS(&DEBUG_UART, prompt);

		commsToPis(buffer, 1);
		//go to Pi1 transmission code
		break;
	case (designatorPi2):

		sprintf(prompt, "commsToPi2");
		putS(&DEBUG_UART, prompt);

		commsToPis(buffer, 2);
		//go to Pi2 transmission code
		break;
	default:
		// ask to re-send packet
		// oops!
		// the first byte you received was not corrected.
		// ignore/dump buffer and tell ground.

		sprintf(prompt, "Invalid designator. Please resend packet number XXX");
		putS(&DEBUG_UART, prompt);

		commsToGround((uint8_t*) prompt);
		return;
	}
	return;
}

void commsToWTC(uint8_t* buffer) {
/*
 * use back door function, inside of command.c/.h
 */
}
void commsToPis(uint8_t* buffer, uint8_t pi) {

}
void commsFromPis(uint8_t* buffer) {

}

/*
 * helper functions
 */

uint8_t isValid_designator() {

	// determine if you will pass the first byte to this function,
	// or if you will update the commsRxPacketStruct after every transmission

	uint8_t d = commsRxPacketStruct->designator;
	if (d != designatorWTC || d != designatorPi1 || d != designatorPi2) {
		return invalidDesignator;
	}

	return commsRxPacketStruct->designator;
}

