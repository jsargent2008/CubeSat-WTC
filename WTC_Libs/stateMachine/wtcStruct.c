/*
 * wtcStruct.c
 *
 *  Created on: May 23, 2018
 *      Author: Administrator
 */

#include "wtcStruct.h"

WTCStatusStruct my_wtc;
WTCStatusStruct *wtc = &my_wtc;


void initWTCStatusStruct() {

//INITIALIZE STRUCTS
	wtc->huartDebug = &DEBUG_UART;
	wtc->hadc = &hadc;
	wtc->hrtc = &hrtc;
	wtc->sAlarm = &sAlarm;

	wtc->deployStruct = deployStruct;
//RTC
	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;

	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);

	//Initial Date Alive
	wtc->startDate = sdatestructureget.Date;
	wtc->startMonth = sdatestructureget.Month;
	wtc->startYear = sdatestructureget.Year;
	//Initial Time Alive
	wtc->startHours = stimestructureget.Hours;
	wtc->startMinutes = stimestructureget.Minutes;
	wtc->startSeconds = stimestructureget.Seconds;

	//start deployment Alarm
	wtc->deployStruct->deployAlarmSet = FALSE;
}
