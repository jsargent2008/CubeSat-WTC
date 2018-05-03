#include "UART_IRQ.h"
#include <stdlib.h>
// The program was created by Theodore Cox
// QPACE

/**
 * @brief  best way to initialize a char array
 * @param  size
 * return char*
 */

char* mallocCharArray(uint32_t size) {
	char* str = malloc(sizeof(char) * (size + 1));
	for (int i = 0; i <= size; i++)
		str[i] = '\0';

	return str;
}

uint32_t arraylength(char* array) {
	if (array == 0)
		return 0;

	uint32_t i = 0;
	while (array[i] != 0)
		i++;

	return i;
}
/**
 * @brief  best way to insert char to a string
 * @param  dest where string will be copied to
 * @param 	src the string to append to the dest string at index 'index'
 * @param	index start location of appending.
 * return  result of the concatenated strings.
 */
char* appendCharArrays(char* dest, char* src, uint32_t index) {
	uint8_t destLen = 0;
	uint8_t srcLen = 0;
	char* result;
	uint8_t inc = 0;
	uint8_t size = 0;
	//find dest string length
	while (dest[inc] != 0) {
		inc++;
	}
	//set dest length
	destLen = inc;

	inc = 0;
	//find src string length
	while (src[inc] != 0) {
		inc++;
	}
	//set src length
	srcLen = inc;

	// if the desired index is larger than the current destination string then append to the end
	if (index > destLen) {
		size = srcLen + index + 1;
		index = destLen; // set index to end of dest string (append)
	} else {
		size = index + srcLen;
		//clear the remaining parts of the string
	}

	result = malloc(sizeof(char) * (size));
	result[size - 1] = 0; // '\n' at the last index

	for (int i = 0; i < index; i++)
		result[i] = dest[i];
	for (int i = index; i < srcLen; i++)
		result[i] = src[i];

	return result;
}

/**
 * @brief  This function is executed when waiting for a UART Interrupt
 * @param  time: the time the program runs.

 */
void UART_IRQ(UART_HandleTypeDef *huart, uint8_t time) {

	int num = huart->State;
	char snum[5];
	snum[3] = '\r';
	snum[4] = '\n';
	itoa(num, snum, 10);

	// print start state
	HAL_UART_Transmit_IT(huart, (uint8_t *) snum, (uint16_t) sizeof(snum));
	HAL_Delay(2);
	char str[7] = "State\n\r";
	HAL_UART_Transmit_IT(huart, (uint8_t *) str, sizeof(snum));
	HAL_Delay(2);

	//until state is ready, print state
	while (huart->State != HAL_UART_STATE_READY) {
		//print state of UART
		int num = huart->State;
		char snum[5];
		snum[3] = '\r';
		itoa(num, snum, 10);
		HAL_UART_Transmit_IT(huart, (uint8_t *) snum, sizeof(snum));
		HAL_Delay(2);
	}
	// Receive
	uint8_t rbuffer[5];
	HAL_UART_Receive_IT(huart, rbuffer, sizeof(rbuffer));
	rbuffer[4] = '\n';
	HAL_Delay(2);
	//Interrupt received
	uint8_t tbuffer[6] = "IRQ!\r\n";
	HAL_UART_Transmit_IT(huart, tbuffer, sizeof(tbuffer));
	// transmit back what was received
	HAL_UART_Transmit_IT(huart, rbuffer, sizeof(rbuffer));

}

void UART_printSOS(UART_HandleTypeDef *huart, uint32_t time) {

	uint32_t i;
	//can loop up to decimal value 2^32
	for (i = 0; i < time; i++) {

		char str[8] = { "S.O.S.\r\n" };

		// print s.o.s.
		HAL_UART_Transmit(huart, (uint8_t *) str, (uint16_t) sizeof(str), 0xFFFF);
		HAL_Delay(500);
	}
}

void UART_PUT(UART_HandleTypeDef *huart, char *str) {
	HAL_UART_Transmit(huart, (uint8_t *) str, (uint16_t) sizeof(str), 0xFFFF);
}

void getS(UART_HandleTypeDef *huart, uint8_t * buf, uint8_t len) {
	//HAL_UART_Receive(&huart3, (uint8_t *) buf, len, 0xFFFF);
	//buf[strlen(buf)] = '\0';
	HAL_UART_Receive(huart, (uint8_t *) buf, len + 1, 0xFFFF);
	buf[strlen(buf) - 1] = '\0';
}

void putS(UART_HandleTypeDef *huart, char* buf) {

	uint8_t size = 0;

	while (buf[size] != 0)
		size++;

	//
	// sizeof DOESNT NOT WORK!!!!!!!!!
	// HAL_UART_Transmit(&huart3, (uint8_t *) buf, (uint16_t) sizeof(buf), 0xFFFF);
	HAL_UART_Transmit(huart, (uint8_t *) buf, (uint16_t) size, 0xFFFF);

}
