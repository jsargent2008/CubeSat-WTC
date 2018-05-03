/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l1xx_hal.h"

/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "LTC2991/LTC2991.h"
#include "UART_IRQ/UART_IRQ.h"
#include "command/command.h"
#include "PRINTF/printf.h"
#include "adc/adc.h"
#include "rtc/rtc.h"
#include "memoryMap/memoryMap.h"

//huart4 is the 70cm primary
#define DEBUG_UART huart1

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

I2C_HandleTypeDef hi2c2;

RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart4;
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

/* RTC handler declaration */
RTC_HandleTypeDef RtcHandle;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_UART4_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_I2C2_Init(void);
static void MX_ADC_Init(void);
static void MX_USART3_UART_Init(void);
static void MX_RTC_Init(void);

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

uint8_t aRxBuffer[10];
char prompt[100] = { };

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	/* Turn LED2 on: Transfer in reception process is correct */
	HAL_GPIO_WritePin(_12V_1_Enable_GPIO_Port, _12V_1_Enable_Pin, GPIO_PIN_SET);

//	sprintf(prompt, "rdone");
	HAL_UART_Transmit(&huart1, (uint8_t *) aRxBuffer, (uint16_t) strlen(aRxBuffer), 0xFFFF);

}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
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
//	while(1){
//
//	putS(&huart4, message);
//	HAL_Delay(500);
//	}
	//gpio port d pin 11 --> d11 is the yellow LED for testing (pwr enable pi 1)

	for (;;) {
		uint8_t aRxBuffer[20] = "";

		//tx "Waiting for command..."
		char *prompt = mallocCharArray(sizeof(message));
		strcpy(prompt, (char*) message);
		putS(&DEBUG_UART, prompt);
		free(prompt);

		// print "cmdXX:""
		prompt = mallocCharArray(20);
		prompt[0] = 'c';
		prompt[1] = 'm';
		prompt[2] = 'd';
		prompt[3] = index / 10 + '0';
		prompt[4] = (index % 10) + '0';
		prompt[5] = ':';

		//noticed that using a new string would prevent the rxbuffer
		// from being altered by the strcmp function.
		// next; check why strcmp affacts the input string (rxbuffer).
		uint8_t tempBuff[20] = "";
		strcpy((char *) tempBuff, (char *) prompt);

		//tx "cmdXX:"
		putS(&DEBUG_UART, prompt);
		free(prompt);

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
		else if (strcmp((char *) aRxBuffer, "cc") == 0)
			HAL_GPIO_TogglePin(DAC_REF_Chrg_GPIO_Port, DAC_REF_Chrg_Pin);
		else if (strcmp((char *) aRxBuffer, "lt") == 0)
			ltc(&hi2c2,&DEBUG_UART);
		else {
			prompt = mallocCharArray(4);
			prompt[0] = (char) '?';
			prompt[1] = (char) '?';
			prompt[2] = (char) '\n';
			prompt[3] = (char) '\r';
			putS(&DEBUG_UART, prompt);
			free(prompt);
		}

		//print new line
		prompt = mallocCharArray(2);
		prompt[0] = (char) '\n';
		prompt[1] = (char) '\r';
		putS(&DEBUG_UART, prompt);
		free(prompt);

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
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL3;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* ADC init function */
static void MX_ADC_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  hadc.Init.LowPowerAutoWait = ADC_AUTOWAIT_DISABLE;
  hadc.Init.LowPowerAutoPowerOff = ADC_AUTOPOWEROFF_DISABLE;
  hadc.Init.ChannelsBank = ADC_CHANNELS_BANK_A;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.NbrOfConversion = 1;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* I2C2 init function */
static void MX_I2C2_Init(void)
{

  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* RTC init function */
static void MX_RTC_Init(void)
{

  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;

    /**Initialize RTC Only 
    */
  hrtc.Instance = RTC;
if(HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0) != 0x32F2){
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initialize RTC and set the Time and Date 
    */
  sTime.Hours = 0x16;
  sTime.Minutes = 0x30;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  sDate.WeekDay = RTC_WEEKDAY_TUESDAY;
  sDate.Month = RTC_MONTH_APRIL;
  sDate.Date = 0x24;
  sDate.Year = 0x18;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    HAL_RTCEx_BKUPWrite(&hrtc,RTC_BKP_DR0,0x32F2);
  }

}

/* UART4 init function */
static void MX_UART4_Init(void)
{

  huart4.Instance = UART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART1 init function */
static void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART2 init function */
static void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* USART3 init function */
static void MX_USART3_UART_Init(void)
{

  huart3.Instance = USART3;
  huart3.Init.BaudRate = 9600;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);
  /* DMA1_Channel5_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, EN_Chrg_1_Pin|Reset_C6_Pin|Reset_C6E5_Pin|RF_Deck_Power_Enable_Pin 
                          |UHF_Deploy_2_Pin|UHF_Deploy_1_Pin|Kill_Switch_1_Pin|Kill_Switch_2_Pin 
                          |EN_MPPT_YZ_E1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, WTC_V_Stack_Pin|Pwr_En_Pi1_Pin|Pwr_En_Pi2_Pin|WTC_BUS_Switch_Pi_Select_Pin 
                          |Pi_Heartbeat_Pi2_Pin|Pi_Heartbeat_Pi2D15_Pin|_70cm_Primary_TR_Pin|EN_MPPT_Z__Pin 
                          |EN_MPPT_YZ__Pin|EN_MPPT_YCtr_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, _12V_1_Enable_Pin|_12V_2_Enable_Pin|_70cm_Primary_Enable_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, _5V_Rail_1_Enable_Pin|_70cm_Primary_Select_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(_5V_Rail_2_Enable_GPIO_Port, _5V_Rail_2_Enable_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, EN_MPPT_XZ__Pin|EN_MPPT_XCtr_Pin|EN_MPPT_XZ_Pin|EN_NTC_Drive_Pin 
                          |Deployment_Power_Enable_Pin|UHF_Power_Enable_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : EN_Chrg_1_Pin Reset_C6_Pin Reset_C6E5_Pin RF_Deck_Power_Enable_Pin 
                           UHF_Deploy_2_Pin UHF_Deploy_1_Pin Kill_Switch_1_Pin Kill_Switch_2_Pin 
                           EN_MPPT_YZ_E1_Pin */
  GPIO_InitStruct.Pin = EN_Chrg_1_Pin|Reset_C6_Pin|Reset_C6E5_Pin|RF_Deck_Power_Enable_Pin 
                          |UHF_Deploy_2_Pin|UHF_Deploy_1_Pin|Kill_Switch_1_Pin|Kill_Switch_2_Pin 
                          |EN_MPPT_YZ_E1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : DAC_REF_Chrg_Pin */
  GPIO_InitStruct.Pin = DAC_REF_Chrg_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(DAC_REF_Chrg_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : ADC_REF_Chrg_Pin */
  GPIO_InitStruct.Pin = ADC_REF_Chrg_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ADC_REF_Chrg_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PwrMon_RC_ADC_Pin */
  GPIO_InitStruct.Pin = PwrMon_RC_ADC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(PwrMon_RC_ADC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : WTC_V_Stack_Pin Pwr_En_Pi1_Pin Pwr_En_Pi2_Pin WTC_BUS_Switch_Pi_Select_Pin 
                           Pi_Heartbeat_Pi2_Pin Pi_Heartbeat_Pi2D15_Pin _70cm_Primary_TR_Pin EN_MPPT_Z__Pin 
                           EN_MPPT_YZ__Pin EN_MPPT_YCtr_Pin */
  GPIO_InitStruct.Pin = WTC_V_Stack_Pin|Pwr_En_Pi1_Pin|Pwr_En_Pi2_Pin|WTC_BUS_Switch_Pi_Select_Pin 
                          |Pi_Heartbeat_Pi2_Pin|Pi_Heartbeat_Pi2D15_Pin|_70cm_Primary_TR_Pin|EN_MPPT_Z__Pin 
                          |EN_MPPT_YZ__Pin|EN_MPPT_YCtr_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : _12V_1_Enable_Pin _12V_2_Enable_Pin _70cm_Primary_Enable_Pin */
  GPIO_InitStruct.Pin = _12V_1_Enable_Pin|_12V_2_Enable_Pin|_70cm_Primary_Enable_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : _5V_Rail_1_Enable_Pin _70cm_Primary_Select_Pin */
  GPIO_InitStruct.Pin = _5V_Rail_1_Enable_Pin|_70cm_Primary_Select_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : _5V_Rail_2_Enable_Pin */
  GPIO_InitStruct.Pin = _5V_Rail_2_Enable_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(_5V_Rail_2_Enable_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : Pgood_3V3_1_Pin PD3 */
  GPIO_InitStruct.Pin = Pgood_3V3_1_Pin|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : EN_MPPT_XZ__Pin EN_MPPT_XCtr_Pin EN_MPPT_XZ_Pin EN_NTC_Drive_Pin 
                           Deployment_Power_Enable_Pin UHF_Power_Enable_Pin */
  GPIO_InitStruct.Pin = EN_MPPT_XZ__Pin|EN_MPPT_XCtr_Pin|EN_MPPT_XZ_Pin|EN_NTC_Drive_Pin 
                          |Deployment_Power_Enable_Pin|UHF_Power_Enable_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
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
