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
#include "memoryMap\memoryMap.h"

/* Private variables ---------------------------------------------------------*/
RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

/* Private function prototypes -----------------------------------------------*/
void updateTimeFlash(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, RTC_DateTypeDef *sDate);

#endif /* RTC_H_ */
