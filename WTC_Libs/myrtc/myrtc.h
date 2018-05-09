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
#include "rtc.h"
#include "memoryMap\memoryMap.h"

/* Includes ------------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

/* Private function prototypes -----------------------------------------------*/
void updateTimeFlash(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, RTC_DateTypeDef *sDate);
void startRTCAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm);
void RTC_AlarmConfig(RTC_HandleTypeDef *RtcHandle, RTC_TimeTypeDef *stimestructure,RTC_DateTypeDef *sdatestructure);
void SETUP_RTC_HandleTypeDef(RTC_HandleTypeDef *RtcHandle);
void RTC_TimeShow(RTC_HandleTypeDef *RtcHandle, uint8_t* showtime);
void printTime(UART_HandleTypeDef *huart, RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm, uint8_t printOption);
void printTimeHelper(UART_HandleTypeDef *huart, RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm);


#include "myrtc.c"
#endif /* RTC_H_ */
