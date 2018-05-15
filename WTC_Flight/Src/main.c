/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * Copyright (c) 2018 STMicroelectronics International N.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted, provided that the following conditions are met:
 *
 * 1. Redistribution of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of other
 *    contributors to this software may be used to endorse or promote products
 *    derived from this software without specific written permission.
 * 4. This software, including modifications and/or derivative works of this
 *    software, must execute solely and exclusively on microcontroller or
 *    microprocessor devices manufactured by or for STMicroelectronics.
 * 5. Redistribution and use of this software other than as permitted under
 *    this license is void and will automatically terminate your rights under
 *    this license.
 *
 * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
 * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
 * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l1xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "fatfs.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <myadc/myadc.h>
#include <myprintf/myprintf.h>
#include <myrtc/myrtc.h>
#include "LTC2991/LTC2991.h"
#include "UART_IRQ/UART_IRQ.h"
#include "command/command.h"
#include "memoryMap/memoryMap.h"
#include "stateMachine/stateMachine.h"

//huart4 is the 70cm primary

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
//RTC_TimeTypeDef sTime;
//RTC_DateTypeDef sDate;
RTC_AlarmTypeDef sAlarm;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
int fgetc(FILE *f) {
	char ch;
	while (__HAL_UART_GET_FLAG(&DEBUG_UART, UART_FLAG_RXNE) == RESET)
		;
	HAL_UART_Receive(&DEBUG_UART, (uint8_t*) &ch, 1, 0xFFFF);
	return ch;
}

size_t __read(int Handle, unsigned char * buf, size_t count) {
	while (__HAL_UART_GET_FLAG(&DEBUG_UART, UART_FLAG_RXNE) == RESET)
		;
	HAL_UART_Receive(&DEBUG_UART, (uint8_t *) buf, count, 0xFFFF);
	return count;
}

//"compiler optimization stuff" - clayton
//"i didn't write it though" - also clayton
#pragma GCC push_options
#pragma GCC optimize ("O3")
#pragma GCC pop_options

void dprint(char* str) {
	int len = strlen(str), i;
	for (i = 0; i < len; i++) {
		ITM_SendChar((uint32_t) str[i]);
		HAL_Delay(500);
	}
}

//uint8_t aRxBuffer[20];
uint8_t aTxStartMessage[] =
		"\n\r ****UART-Hyperterminal communication based on DMA****\n\r Enter 10 characters using keyboard :\n\r";
uint8_t aTxEndMessage[] = "\n\r Example Finished\n\r";
uint8_t atick[] = "\n\r TICK \n\r";

uint8_t aRxBuffer[10];
uint8_t prompt[100] = { };

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
//	/* Turn LED2 on: Transfer in reception process is correct */
//	HAL_GPIO_WritePin(_12V_1_Enable_GPIO_Port, _12V_1_Enable_Pin, GPIO_PIN_SET);
//
////	sprintf(prompt, "rdone");
//	HAL_UART_Transmit(&huart1, (uint8_t *) aRxBuffer, (uint16_t) strlen(aRxBuffer), 0xFFFF);
//
	//check if pi interrupt
	if (huart == &UART_Pi1 || huart == &UART_Pi2) {
		;
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {

	//check if pi interrupt
	if (huart == &UART_Pi1 || huart == &UART_Pi2) {
		;
	}
}

//void HAL_RTC_AlarmIRQHandler(RTC_HandleTypeDef *hrtc) {
//	RTC_TimeShow(prompt);
//	putS(&huart4, prompt);
//}
/**
 * @brief  Alarm callback
 * @param  hrtc : RTC handle
 * @retval None
 */
void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) {
	//HAL_GPIO_TogglePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin);
	// RTC delay 30min
//	//*** working
//		RTC_DateTypeDef sdatestructureget;
//		RTC_TimeTypeDef stimestructureget;
//		HAL_RTC_GetTime(hrtc, &stimestructureget, RTC_FORMAT_BIN);
//		HAL_RTC_GetDate(hrtc, &sdatestructureget, RTC_FORMAT_BIN);
//
//		//HAL_RTC_GetAlarm(hrtc, &fuk, RTC_ALARM_A, RTC_FORMAT_BCD);
//
//		sprintf((char*) prompt, "tick(sec) %02d:%02d:%02d\r\n", stimestructureget.Hours,
//				stimestructureget.Minutes, stimestructureget.Seconds);
//		putS(&huart4, prompt);
//	//working *** //
//	RTC_TimeShow(hrtc, prompt);
//	RTC_TimeShow(prompt);
//	putS(&huart4, (char *) prompt);
//	HAL_GPIO_TogglePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin);
//	putS(&huart4,  atick);
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 *
 * @retval None
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration----------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	HAL_StatusTypeDef hal = HAL_Init();
	if (hal == HAL_ERROR) {

	}

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_UART4_Init();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_I2C2_Init();
	MX_ADC_Init();
	MX_USART3_UART_Init();
	MX_RTC_Init();
	MX_SPI1_Init();
	MX_FATFS_Init();
	/* USER CODE BEGIN 2 */
//	(uint32_t)0x08080000
	//uint32_t data = gpioStatusRetrieve('A');
	//gpioDump();
	//RTC testing, the rest of main agrees with master branch
//	while (1) {
//		//updateTimeFlash(&hrtc, &sTime, &sDate);
//		data = data;
//		HAL_Delay(500);
//	}
//	LTC2991 *testLtc = initLTC2991(&hi2c2, 0x90);
//	while (1) {
//		HAL_Delay(500);
////		test(testLtc, &USART_PI1);
//		readAllLTC(testLtc, &USART_PI1);
//		readChannelLTC(testLtc, &USART_PI1, 1);
//		readChannelLTC(testLtc, &USART_PI1, 10);
//	}
//	while (1) {
//
//		/*##-2- Start the transmission process #####################################*/
//		/* User start transmission data through "TxBuffer" buffer */
//		if (HAL_UART_Transmit_DMA(&huart1, (uint8_t *) aTxStartMessage,
//				strlen((char *) aTxStartMessage)) != HAL_OK) {
//			/* Transfer error in transmission process */
//			Error_Handler();
//		}
//
//		while (HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY) {
//		}
//
//		sprintf(prompt, "tdone  ");
//		HAL_UART_Transmit(&huart1, (uint8_t *) prompt, (uint16_t) strlen(prompt), 0xFFFF);
//
//		/*##-3- Put UART peripheral in reception process ###########################*/
//		/* Any data received will be stored in "RxBuffer" buffer : the number max of
//		 data received is 10 */
//		if (HAL_UART_Receive_DMA(&huart1, (uint8_t *) aRxBuffer, 10) != HAL_OK) {
//			/* Transfer error in reception process */
//			Error_Handler();
//		}
//
//		sprintf(prompt, "rdone");
//		HAL_UART_Transmit(&huart1, (uint8_t *) prompt, (uint16_t) strlen(prompt), 0xFFFF);
//
//		/* Infinite loop */
//		while (1) {
//		}
//
//	}
	//char lcdstring[50] = "";
	//used for "cmdXX" string
	uint8_t index = 0;
	char *message = "Waiting for command...\n\r";

	//HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);

	// Delay to allow SD card to get set up internally.
	HAL_Delay(1000);

	// Common results variable for most of the FatFs function calls.
	// FR_OK = 0, any other result is an error and non-zero.
	FRESULT fres;

	// Mount the SD card.
	fres = f_mount(&USERFatFS, "", 1);
	if (fres != FR_OK) {
		while (1)
			; // Fatal SD mounting error.
	}


	// Demo of grabbing individual packets. Right now, splits packets on 'es'
	// so any time 'e' and 's' appear together, that marks the start of another
	// packet. Can be changed to any byte value, even non-ASCII. This demo
	// doesn't actually do anything with the data, just stores it in `packet`.
	// To make sure it's working, breakpoint on the free(packet) line and inspect
	// the local variable `*packet`, it should contain the bytes. Note that it will
	// show more than the actual buffer size in the debug window, since there is no
	// null terminator. Rest assured, the garbage after the correct values is expected
	// and harmless.
	int32_t p_size = 0, p_num = 1;
	do {
		uint8_t* packet = NULL;
		p_size = get_packet(p_num++, &packet);
		free(packet);
	} while (p_size > 0);

	// Unmount the SD card when finished.
	// Not sure if we'll have to actually do this before the Pi can read and write to it?
	// Or if we just have to ensure we're not also reading and writing while the Pi is.
	f_mount(NULL, "", 0);

//	RTC_TimeShow(&hrtc, prompt);
//	putS(&huart4, prompt);

//HAL_Alarm
//	while (1) {
////		wtcSetup(&huart4,&hadc, &hrtc, &sAlarm);
////		RTC_TimeShow(&hrtc, prompt);
////		putS(&huart4, prompt);
//		HAL_Delay(500);
//	}
	//gpio port d pin 11 --> d11 is the yellow LED for testing (pwr enable pi 1)

	for (;;) {
		char aRxBuffer[20] = "";

//		//tx "Waiting for command..."
		char prompt[100] = { };
		putS(&DEBUG_UART, message);

		sprintf((char*) prompt, "cmd%d%d:", (index / 10), ((index % 10)));
		putS(&DEBUG_UART, prompt);

		//		read in two character command
		getS(&DEBUG_UART, aRxBuffer, 2);

		if (strcmp((char *) aRxBuffer, "dw") == 0)
			dw(&DEBUG_UART);
		else if (strcmp((char *) aRxBuffer, "dr") == 0)
			dr(&DEBUG_UART);
		else if (strcmp((char *) aRxBuffer, "aw") == 0)
			aw(&DEBUG_UART);
		else if (strcmp((char *) aRxBuffer, "ar") == 0)
			ar(&DEBUG_UART, &hadc);
		else if (strcmp((char *) aRxBuffer, "tt") == 0)
			tt(&DEBUG_UART, &huart2);
		else if (strcmp((char *) aRxBuffer, "ks") == 0)
			ks(&DEBUG_UART);
		else if (strcmp((char *) aRxBuffer, "ce") == 0)
			HAL_GPIO_TogglePin(EN_Chrg_1_GPIO_Port, EN_Chrg_1_Pin);
#ifndef SD_CS_Pin // TODO: fix hackish QPace/SurfSat switch
		else if (strcmp((char *) aRxBuffer, "cc") == 0)
		HAL_GPIO_TogglePin(DAC_REF_Chrg_GPIO_Port, DAC_REF_Chrg_Pin);
#endif
		else if (strcmp((char *) aRxBuffer, "lt") == 0)
			ltc(&hi2c2, &DEBUG_UART);
		else if (strcmp((char *) aRxBuffer, "dp") == 0)
			wtcSetup(&DEBUG_UART, &hadc, &hrtc, &sAlarm);
		else {
			sprintf((char*) prompt, "??\r\n");
			putS(&DEBUG_UART, prompt);
		}

//		//print new line
		sprintf((char*) prompt, "\r\n");
		putS(&DEBUG_UART, prompt);

		//increment main forloop index, numbering of command sent.
		index++;
		if (index >= 100)
			index = 0;
	}
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {

		/*******
		 * JON START HERE
		 */

//		if (HAL_FLASHEx_DATAEEPROM_Unlock() == HAL_OK) // Remember to unlock the EEPROM before using
//				{
//			//		  HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD,0x08080000,555); //Write: Type, Address, Data
//			uint32_t data_in = *(uint32_t *) 0x08080000; //Read: Cast the address as a uint32_t pointer and dereference it
//			HAL_FLASHEx_DATAEEPROM_Lock(); //Lock when done? (Not sure if necessary)
//		}
		/*******
		 * JON END HERE
		 */
	}
	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
	for (;;) {

//	  HAL_ADC
		HAL_ADC_Start(&hadc);
		HAL_ADC_PollForConversion(&hadc, 100);
		uint32_t val = HAL_ADC_GetValue(&hadc);
		UNUSED(val);

//		float val2 = adcToVoltage(&hadc);
//		UNUSED(val2);
		HAL_ADC_Stop(&hadc);
//	  EN_Chrg_1_GPIO_Port
	}

	/* USER CODE END 3 */

}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {

	RCC_OscInitTypeDef RCC_OscInitStruct;
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_PeriphCLKInitTypeDef PeriphClkInit;

	/**Configure the main internal regulator output voltage
	 */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = 16;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL3;
	RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1
			| RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
	if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure the Systick interrupt time
	 */
	HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

	/**Configure the Systick
	 */
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  file: The file name as string.
 * @param  line: The line in file as a number.
 * @retval None
 */
void _Error_Handler(char *file, int line) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
