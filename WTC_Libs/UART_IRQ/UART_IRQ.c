#include "UART_IRQ.h"
#include <stdlib.h>
// The program was created by Theodore Cox
// QPACE


/**
  * @brief  This function is executed when waiting for a UART Interrupt
  * @param  time: the time the program runs.
  */
	void UART_IRQ(UART_HandleTypeDef *huart, uint8_t time){

		int num = huart->State;
		char snum[5];
		snum[3] = '\r';
		snum[4] = '\n';
		itoa(num, snum, 10);

		// print start state
		HAL_UART_Transmit_IT(huart, (uint8_t *)snum, (uint16_t)sizeof(snum));
		HAL_Delay(2);
		char str[7] = "State\n\r";
		HAL_UART_Transmit_IT(huart, (uint8_t *)str, sizeof(snum));
		HAL_Delay(2);

		//until state is ready, print state
		while(huart->State != HAL_UART_STATE_READY)
		{
			//print state of UART
			int num = huart->State;
			char snum[5];
			snum[3] = '\r';
			itoa(num, snum, 10);
			HAL_UART_Transmit_IT(huart, (uint8_t *)snum, sizeof(snum));
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


	void UART_printSOS(UART_HandleTypeDef *huart, uint32_t time){

		uint32_t i;
		//can loop up to decimal value 2^32
		for(i = 0; i < time; i++)
		{

			char str[8] = {"S.O.S.\r\n"};

			// print s.o.s.
			HAL_UART_Transmit(huart, (uint8_t *)str, (uint16_t)sizeof(str), 0xFFFF);
			HAL_Delay(500);
		}
	}
