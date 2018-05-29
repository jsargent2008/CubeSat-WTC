/*
 * SS_Pi_Comms.c
 *
 *  Created on: May 29, 2018
 *      Author: Administrator
 */

#include "SS_Pi_Comms.h"

/*
 * ground to pi
 * arguments:
 * 			pi (first byte of packet - used to channel which pi the packet will be sent to)
 * 			packet - 128 byte packet (including designator byte, time start, time stop, and data) // data is hidden from WTC
 */
uint8_t SS_GndToPi(uint8_t pi, uint8_t *packet, uint8_t timeStart, uint8_t timeStop) {

	uint8_t numOfParitions = 4;
	char prompt[100] = "";
	char ack[] = "ok";
	char rxAck[3] = "";
	uint32_t txBuffer[4];
	uint8_t ackLen = strlen((char *) ack);

	UART_HandleTypeDef huart;
	//determine which UART to use
	switch (pi) {
	case (1):
		huart = UART_Pi1;
		break;
	case (2):
		huart = UART_Pi2;
		break;
	default:
		return FLAG_WRONG_PI;
	}

	/*
	 * make sure that the start time agrees with the RTC clock
	 * return FLAG_WRONG_TIME if needed to wait.
	 */

	//...
	//send a 'start of conversation' message
	putS(&huart, "Sending packet");
	HAL_Delay(200);
	getS(&huart, rxAck, ackLen);

	if (strcmp(rxAck, ack) != 0) {
		// EXCEEDED ALLOWED ATTEMPTS
		//send end of transmission
		putS(&huart, "ERR..EOT");
		HAL_Delay(100);
		return FLAG_ERR_START;
	}

	//break packet into partitions
	for (int i = 0; i < numOfParitions; i++) {
		txBuffer[i] = packet[4*i];
	}

	/*
	 * if attempts per partition exceed 5, then move on to the next one and complete
	 */

	uint8_t attemptLimit = 5;
	uint8_t attempt = 0;
	//attempt to send partitions/packet
	for (int i = 0; i < numOfParitions; i++) {

		sprintf(prompt, "%d", (int) txBuffer[i]);
		putS(&huart, prompt);

		HAL_Delay(100);
		//wait for rx-buffer to become full
		//...

		getS(&huart, rxAck, ackLen);

		//wait for an acknowledgment ("ok") back
		//if it doesn't equate to "ok" re-send partition
		if (strcmp(rxAck, ack) != 0) {
			attempt++;
			i--;
			putS(&huart, "re-sending");
			HAL_Delay(200);
		} else {
			attempt = 0;
		}

		if (attempt > attemptLimit) {
			//EXCEEDED ALLOWED ATTEMPTS
			//send end of transmission
			putS(&huart, "ERR..EOT");
			HAL_Delay(1000);

			return FLAG_ERR_ACK;
		}
	}

	/*
	 * ask for partitions back from pi
	 * check if they are the same as transmitted
	 */
	char rxPacket[128] = "";
	putS(&huart, "send back");
	HAL_Delay(200);
	//wait for pi to send back packet
	getS(&huart, rxPacket, ackLen);

	if (strcmp((char *)rxPacket, (char*)packet) == 0) {
		return 0;
	} else{
		return FLAG_ERR_TRANSMISSION;
	}
}

