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

	uint8_t numOfPartitions = 4;
//	char prompt[100] = "";
	//char ack[] = "OK"; //char ack[] = "OK";
	char rxAck[20] = "";
	uint8_t ackLen = strlen((char *) ack);

	//determine which UART to use
	UART_HandleTypeDef *huart = switchUART(pi);
	if (huart == NULL) {
		return FLAG_WRONG_PI;
	}

	/*
	 * make sure that the start time agrees with the RTC clock
	 * return FLAG_WRONG_TIME if needed to wait.
	 */

	//...
	//send a 'start of conversation' message
	putS(huart, "Sending packet\r\n");
	getS(huart, rxAck, 2);
	//char rxAck[20] = "";
	//HAL_UART_Receive(&UART_Pi1, (uint8_t *)rxAck, 3, 1000);
	//putS(&huart2, rxAck);
	//rxAck[strlen((rxAck)) - 1] = '\0';

	if (strcmp(rxAck, ack) != 0) {
		// EXCEEDED ALLOWED ATTEMPTS
		//send end of transmission
		putS(&huart1, "ERR..EOT\r\n");
		HAL_Delay(100);
		return FLAG_ERR_START;
	}

	uint8_t *txBuffer[4];
	for (int i = 0; i < numOfPartitions; i++) {
		txBuffer[i] = malloc(sizeof(uint8_t) * 32); //should point to the 4 tx Packet partitions
	}

	//break packet into partitions
	//default 4 partitions
	for (int i = 0; i < numOfPartitions; i++) {
		//default - 32 bytes per partition
		memcpy(txBuffer[i], packet + (32 * i), 32);
	}

	/*
	 * if attempts per partition exceed 5, then move on to the next one and complete
	 */

	uint8_t attemptLimit = 5;
	uint8_t attempt = 0;
	//attempt to send partitions/packet
	for (int i = 0; i < numOfPartitions; i++) {

		//sprintf(prompt, "%s\", txBuffer[i]);
		putB(&huart1, (char *) txBuffer[i], 32);
		//wait for rx-buffer to become full
		//...

		getS(huart, rxAck, ackLen);
		//HAL_UART_Receive(&UART_Pi1, (uint8_t *)rxAck, 3, 0xFFFF);
		//putS(&huart2, rxAck);
		//if it doesn't equate to "ok" re-send partition
		if (strcmp(rxAck, ack) != 0) {
			attempt++;
			i--;
			putS(&huart1, "re-sending\r\n");
			HAL_Delay(200);
		} else {
			attempt = 0;
		}

		if (attempt > attemptLimit) {
			//EXCEEDED ALLOWED ATTEMPTS
			//send end of transmission
			putS(&huart1, "ERR..EOT\r\n");
			HAL_Delay(1000);

			return FLAG_ERR_ACK;
		}
	}

	//free temp buffer
	for (int i = 0; i < numOfPartitions; i++) {
		free(txBuffer[i]);
		txBuffer[i] = NULL;
		//putB(huart, (char *) txBuffer[i], 32);
	}

	/*
	 * ask for partitions back from pi
	 * check if they are the same as transmitted
	 */
	char rxPacket[128] = "";
	putS(huart, "send back\r\n");
	//wait for pi to send back packet
	getB(huart, rxPacket, 128);
	//HAL_UART_Receive(&UART_Pi1, (uint8_t *)rxPacket, 3, 1000);
	if (memcmp(rxPacket, packet, 128) == 0) {
		putS(&huart1, "OK..EOT\r\n");
		getS(huart, rxAck, 2);
		//HAL_Delay(200);
		return 0;
	} else {
		putS(&huart1, "ERR..EOT\r\n");
		getS(huart, rxAck, 2);
		//HAL_Delay(200);
		return FLAG_ERR_TRANSMISSION;
	}
}

/*
 *	this function should be called when the pi is done with its experiment
 *	is it being called by a timer? or when the pi says its ready?
 */

uint8_t SS_PiToSD(uint8_t pi, uint8_t *packet, uint8_t timeStart, uint8_t timeStop,
		uint8_t interrupt) {

	//cases when this function is called:
	//if called by interrupt, no checking that the pi is ready needs to be done

	//if time limit for the experiment is exceeded then the pi-to-wtc handshake needs to occur
	//if battery voltage drops then the pi needs to be notified (preferably outside of this function and then a call
	//to this function should occur

	//determine which UART to use
	UART_HandleTypeDef *huart = switchUART(pi);
	if (huart == NULL) {
		return FLAG_WRONG_PI;
	}

	char rxPacket[128] = "";
	char rxTemp[128] = "";


	putS(huart, "send data\r\n");
	//wait for pi to send back packet
	getB(huart, rxPacket, 128);
	memcpy(rxTemp,rxPacket,128);
	putS(&huart2, rxTemp);
	//uint8_t partition[4] = unpacketize(rxPacket);
	SS_GndToPi(1, (uint8_t*)rxPacket, 0, 0);
	return 0;
}

/*
 * assuming that buffer is an allocated 128-byte block
 */
uint8_t checkStartStopByte(uint8_t * buf) {

	uint8_t * tempStartByte = malloc(sizeof(uint8_t) * 8);
	uint8_t * tempStopByte = malloc(sizeof(uint8_t) * 8);

	if (tempStartByte == NULL || tempStopByte == NULL) {
		return 0;
	}

	// TODO: Is this supposed to just be one byte? The macros SS_Pi_[START|STOP]_BYTE are just single bytes,
	//       not a buffer of 8 bytes. If so, the code should become:

	/*tempStartByte = buf[0];
	tempStopByte = buf[127];*/

	// Or even better, ditch the temp variables and use the buf[x] calls directly.

	memcpy(tempStartByte, buf, 8);
	memcpy(tempStartByte, buf + 120, 8);

	if (*tempStartByte != SS_Pi_START_BYTE) {
		return FLAG_ERR_Pi_START_BYTE;
	} else if (*tempStopByte != SS_Pi_STOP_BYTE) {
		return FLAG_ERR_Pi_STOP_BYTE;
	}
	return true;
}

/*
 * function should only be used as a helper for the other functions in this c file.
 * removes redundant coding
 * NOTE: if using this function, check for NULL ('num' value not valid)
 */
UART_HandleTypeDef *switchUART(uint8_t num) {

	/*
	 * num: 1 = pi1			huart1
	 * 		2 = pi2			huart3
	 * 		3 = secondary	huart2
	 * 		4 = primary		huart4
	 *
	 */

	UART_HandleTypeDef *huart;

	switch (num) {
	case (1):
		//pi 1
		huart = &UART_Pi1;
		break;
	case (2):
		//pi2
		huart = &UART_Pi2;
		break;
	case (3):
		//secondary
		huart = &huart2;
		break;
	case (4):
		//primary
		huart = &DEBUG_UART;
		break;
	default:
		huart = NULL;
	}

	return huart;
}

/*
 * 4 32-bytes to 128-byte packets
 * partition should be a char[4] of 32-bytes
 */
uint8_t *packetize(char *partition) {

	uint8_t *packet = malloc(sizeof(uint8_t) * 128);

	const uint8_t partSize = 32;
	for (int i = 0; i < 4; i++) {
		memcpy(packet + i * partSize, partition + (partSize * i), partSize);
	}

	return packet;
}

/*
 * 128-bytes to 4 32-byte packets
 */
uint8_t** unpacketize(uint8_t *packet) {
	uint8_t** partition = malloc(sizeof(uint8_t*) * 4);
	for (int i = 0; i < 4; i++) {
		partition[i] = malloc(sizeof(uint8_t) * 32); //should point to the 4 tx Packet partitions
	}

	//break packet into partitions
	//default 4 partitions
	for (int i = 0; i < 4; i++) {
		//default - 32 bytes per partition
		memcpy(partition[i], packet + (32 * i), 32);
	}

	return partition;
}

