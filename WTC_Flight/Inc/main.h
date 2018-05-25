/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

/* USER CODE BEGIN Includes */
//#include "stm32l1xx_hal.h"
//#include "stm32l1xx_hal_i2c.h"
/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define EN_Chrg_1_Pin GPIO_PIN_3
#define EN_Chrg_1_GPIO_Port GPIOE
#define Reset_C6_Pin GPIO_PIN_4
#define Reset_C6_GPIO_Port GPIOE
#define Reset_C6E5_Pin GPIO_PIN_5
#define Reset_C6E5_GPIO_Port GPIOE
#define _5X_Out_3_Pin GPIO_PIN_0
#define _5X_Out_3_GPIO_Port GPIOC
#define _5X_Out_2_Pin GPIO_PIN_1
#define _5X_Out_2_GPIO_Port GPIOC
#define _5X_Out_1_Pin GPIO_PIN_2
#define _5X_Out_1_GPIO_Port GPIOC
#define _10X_Out_1_Pin GPIO_PIN_3
#define _10X_Out_1_GPIO_Port GPIOC
#define MPPT_BUS_MON_Pin GPIO_PIN_1
#define MPPT_BUS_MON_GPIO_Port GPIOA
#define UART_TX_RF_Deck_Pin GPIO_PIN_2
#define UART_TX_RF_Deck_GPIO_Port GPIOA
#define UART_RX_RF_Deck_Pin GPIO_PIN_3
#define UART_RX_RF_Deck_GPIO_Port GPIOA
#define _20X_Out_1_Pin GPIO_PIN_4
#define _20X_Out_1_GPIO_Port GPIOC
#define STM_PC5_ADC_Pin GPIO_PIN_5
#define STM_PC5_ADC_GPIO_Port GPIOC
#define lmon_3_3_2_Pin GPIO_PIN_0
#define lmon_3_3_2_GPIO_Port GPIOB
#define lmon_3_3_1_Pin GPIO_PIN_1
#define lmon_3_3_1_GPIO_Port GPIOB
#define RF_Deck_Power_Enable_Pin GPIO_PIN_7
#define RF_Deck_Power_Enable_GPIO_Port GPIOE
#define PwrMon_RC_ADC_Pin GPIO_PIN_9
#define PwrMon_RC_ADC_GPIO_Port GPIOE
#define _70cm_AUX_ADC_Pin GPIO_PIN_10
#define _70cm_AUX_ADC_GPIO_Port GPIOE
#define UHF_Deploy_2_Pin GPIO_PIN_11
#define UHF_Deploy_2_GPIO_Port GPIOE
#define UHF_Deploy_1_Pin GPIO_PIN_12
#define UHF_Deploy_1_GPIO_Port GPIOE
#define Kill_Switch_1_Pin GPIO_PIN_14
#define Kill_Switch_1_GPIO_Port GPIOE
#define Kill_Switch_2_Pin GPIO_PIN_15
#define Kill_Switch_2_GPIO_Port GPIOE
#define V_Stack_1_Meas_Pin GPIO_PIN_12
#define V_Stack_1_Meas_GPIO_Port GPIOB
#define V_Stack_2_Meas_Pin GPIO_PIN_13
#define V_Stack_2_Meas_GPIO_Port GPIOB
#define V_Stack_3_Meas_Pin GPIO_PIN_14
#define V_Stack_3_Meas_GPIO_Port GPIOB
#define V_Stack_4_Meas_Pin GPIO_PIN_15
#define V_Stack_4_Meas_GPIO_Port GPIOB
#define UART_TXD_Pi2_Pin GPIO_PIN_8
#define UART_TXD_Pi2_GPIO_Port GPIOD
#define UART_RXD_Pi2_Pin GPIO_PIN_9
#define UART_RXD_Pi2_GPIO_Port GPIOD
#define WTC_V_Stack_Pin GPIO_PIN_10
#define WTC_V_Stack_GPIO_Port GPIOD
#define Pwr_En_Pi1_Pin GPIO_PIN_11
#define Pwr_En_Pi1_GPIO_Port GPIOD
#define Pwr_En_Pi2_Pin GPIO_PIN_12
#define Pwr_En_Pi2_GPIO_Port GPIOD
#define WTC_BUS_Switch_Pi_Select_Pin GPIO_PIN_13
#define WTC_BUS_Switch_Pi_Select_GPIO_Port GPIOD
#define Pi_Heartbeat_Pi2_Pin GPIO_PIN_14
#define Pi_Heartbeat_Pi2_GPIO_Port GPIOD
#define Pi_Heartbeat_Pi2D15_Pin GPIO_PIN_15
#define Pi_Heartbeat_Pi2D15_GPIO_Port GPIOD
#define _12V_1_Enable_Pin GPIO_PIN_8
#define _12V_1_Enable_GPIO_Port GPIOC
#define _12V_2_Enable_Pin GPIO_PIN_9
#define _12V_2_Enable_GPIO_Port GPIOC
#define UART_TXD_Pi1_Pin GPIO_PIN_9
#define UART_TXD_Pi1_GPIO_Port GPIOA
#define UART_RXD_Pi1_Pin GPIO_PIN_10
#define UART_RXD_Pi1_GPIO_Port GPIOA
#define SD_CS_Pin GPIO_PIN_11
#define SD_CS_GPIO_Port GPIOA
#define _5V_Rail_1_Enable_Pin GPIO_PIN_12
#define _5V_Rail_1_Enable_GPIO_Port GPIOA
#define _5V_Rail_2_Enable_Pin GPIO_PIN_2
#define _5V_Rail_2_Enable_GPIO_Port GPIOH
#define _70cm_Primary_Select_Pin GPIO_PIN_15
#define _70cm_Primary_Select_GPIO_Port GPIOA
#define _70cm_Primary_UART_TX_Pin GPIO_PIN_10
#define _70cm_Primary_UART_TX_GPIO_Port GPIOC
#define _70cm_Primary_UART_RX_Pin GPIO_PIN_11
#define _70cm_Primary_UART_RX_GPIO_Port GPIOC
#define _70cm_Primary_Enable_Pin GPIO_PIN_12
#define _70cm_Primary_Enable_GPIO_Port GPIOC
#define _70cm_Primary_TR_Pin GPIO_PIN_0
#define _70cm_Primary_TR_GPIO_Port GPIOD
#define Pgood_3V3_1_Pin GPIO_PIN_2
#define Pgood_3V3_1_GPIO_Port GPIOD
#define EN_MPPT_Z__Pin GPIO_PIN_5
#define EN_MPPT_Z__GPIO_Port GPIOD
#define EN_MPPT_YZ__Pin GPIO_PIN_6
#define EN_MPPT_YZ__GPIO_Port GPIOD
#define EN_MPPT_YCtr_Pin GPIO_PIN_7
#define EN_MPPT_YCtr_GPIO_Port GPIOD
#define EN_MPPT_XZ__Pin GPIO_PIN_4
#define EN_MPPT_XZ__GPIO_Port GPIOB
#define EN_MPPT_XCtr_Pin GPIO_PIN_5
#define EN_MPPT_XCtr_GPIO_Port GPIOB
#define EN_MPPT_XZ_Pin GPIO_PIN_6
#define EN_MPPT_XZ_GPIO_Port GPIOB
#define EN_NTC_Drive_Pin GPIO_PIN_7
#define EN_NTC_Drive_GPIO_Port GPIOB
#define Deployment_Power_Enable_Pin GPIO_PIN_8
#define Deployment_Power_Enable_GPIO_Port GPIOB
#define UHF_Power_Enable_Pin GPIO_PIN_9
#define UHF_Power_Enable_GPIO_Port GPIOB
#define EN_MPPT_YZ_E1_Pin GPIO_PIN_1
#define EN_MPPT_YZ_E1_GPIO_Port GPIOE

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */
#define USART_PRIMARY huart4
#define USART_PI1 huart1
#define USART_UHF huart2
#define USART_PI2 huart3

#define TRUE 1
#define true 1
#define FALSE 0
#define false 0

#define packetSize_IT 8//128
char DMABUFFER[packetSize_IT];
/**
 * remove before flight
 */
// only set to 1687 if ready to release deployment
#define DEPLOYACCESSCODE 1 /*1687*/

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
