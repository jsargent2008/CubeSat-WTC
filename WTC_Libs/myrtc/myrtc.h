/*
 * rtc.h
 *
 *  Created on: Apr 24, 2018
 *      Author: Theodore Cox
 */

#ifndef RTC_H_
#define RTC_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_def.h"
#include "stm32l1xx_hal_rtc.h"
#include "rtc.h"
#include "usart.h"
#include "UART_IRQ\UART_IRQ.h"
#include "memoryMap\memoryMap.h"
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_uart.h"

/* Includes ------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

/* Private function prototypes -----------------------------------------------*/
void updateTimeFlash(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, RTC_DateTypeDef *sDate);
void startRTCAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm);
void RTC_AlarmConfig(RTC_HandleTypeDef *RtcHandle, RTC_TimeTypeDef *stimestructure,
		RTC_DateTypeDef *sdatestructure);
void SETUP_RTC_HandleTypeDef(RTC_HandleTypeDef *RtcHandle);
void RTC_TimeShow(RTC_HandleTypeDef *RtcHandle, uint8_t* showtime);
void printTime(uint8_t printOption);
void printTimeHelper();

#endif /* RTC_H_ */
