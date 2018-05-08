/*
 * rtc.c
 *
 *  Created on: Apr 7, 2018
 *      Author: Administrator
 */
#include "rtc.h"

//	The following private function protoypes should be in main,
// 	generated by the stm32 cube.
/* Private function prototypes -----------------------------------------------*/
static void RTC_AlarmConfig(RTC_HandleTypeDef *RtcHandle, RTC_TimeTypeDef *stimestructure,
		RTC_DateTypeDef *sdatestructure);
static void RTC_TimeShow(RTC_HandleTypeDef *RtcHandle, uint8_t* showtime);

/**
 * @brief  update flash with RTC time and date
 * @param  hrtc pointer
 * @param  sTime pointer
 * @param  sDate pointer
 * @retval void...
 */
void updateTimeFlash(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, RTC_DateTypeDef *sDate) {
	//HAL_StatusTypeDef HAL_RTC_GetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format)
	/*Get  the RTC current Time*/
	HAL_RTC_GetTime(hrtc, sTime, RTC_FORMAT_BIN);
	/*Get  the RTC current Date*/
	HAL_RTC_GetDate(hrtc, sDate, RTC_FORMAT_BIN);

	uint32_t time_32 = 0;
	time_32 = sTime->Hours;
	time_32 = time_32 << 8;
	time_32 = time_32 ^ sTime->Minutes;
	time_32 = time_32 << 8;
	time_32 = time_32 ^ sTime->Seconds;
	time_32 = time_32 << 8;

	uint32_t date_32 = 0;
	date_32 = sDate->Date;
	date_32 = date_32 << 8;
	date_32 = date_32 ^ sDate->Month;
	date_32 = date_32 << 8;
	date_32 = date_32 ^ sDate->Year;
	date_32 = date_32 << 8;

	// Remember to unlock the EEPROM before using
	if (HAL_FLASHEx_DATAEEPROM_Unlock() == HAL_OK) {
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, sysMem_lastChk_RTC_Time,
				time_32);
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, sysMem_lastChk_RTC_Date,
				date_32);
		//access time and date with the followig lines
		//uint32_t data_time = *(uint32_t *) sysMem_lastChk_RTC_Time; //Read: Cast the address as a uint32_t pointer and dereference it
		//uint32_t data_date = *(uint32_t *) sysMem_lastChk_RTC_Date; //Read: Cast the address as a uint32_t pointer and dereference it
		HAL_FLASHEx_DATAEEPROM_Lock(); //Lock when done? (Not sure if necessary)
	}

	HAL_Delay(10);
}

void startRTCAlarm(RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm) {

	uint32_t Format = RTC_FORMAT_BIN; //bin-0 BCD-1
	HAL_RTC_SetAlarm(hrtc, sAlarm, Format);

}

/*****************************************************************************************************************************/
// CODE BELOW SHOULD BE GENERATED BY STM32 CUBE
// THIS SHOULD BE MOVED TO MAIN, through the cube.
RTC_HandleTypeDef SETUP_RTC_HandleTypeDef(RTC_HandleTypeDef *RtcHandle) {

	/*##-1- Configure the RTC peripheral #######################################*/
	RtcHandle->Instance = RTC;

	/* Configure RTC prescaler and RTC data registers */
	/* RTC configured as follows:
	 - Hour Format    = Format 24
	 - Asynch Prediv  = Value according to source clock
	 - Synch Prediv   = Value according to source clock
	 - OutPut         = Output Disable
	 - OutPutPolarity = High Polarity
	 - OutPutType     = Open Drain */
	RtcHandle->Init.HourFormat = RTC_HOURFORMAT_24;
	//RtcHandle->Init.AsynchPrediv = 	IS_RTC_ASYNCH_PREDIV;
	//RtcHandle->Init.SynchPrediv = 	IS_RTC_ASYNCH_PREDIV;
	RtcHandle->Init.OutPut = RTC_OUTPUT_DISABLE;
	RtcHandle->Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	RtcHandle->Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
}
/**
 // * @brief  Alarm callback
 // * @param  hrtc : RTC handle
 // * @retval None
 // */
//void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc) {
//
//	//Do something if alarm is turned on.
//}
/**
 * @brief  Configure the current time and date.
 * @param  None
 * @retval None
 */
static void RTC_AlarmConfig(RTC_HandleTypeDef *RtcHandle, RTC_TimeTypeDef *stimestructure,
		RTC_DateTypeDef *sdatestructure) {
	//RTC_DateTypeDef sdatestructure;
	//RTC_TimeTypeDef stimestructure;
	RTC_AlarmTypeDef salarmstructure;

	/*##-1- Configure the Date #################################################*/
	/* Set Date: Tuesday February 18th 2014 */
//	sdatestructure.Year = 0x14;
//	sdatestructure.Month = RTC_MONTH_FEBRUARY;
//	sdatestructure.Date = 0x18;
//	sdatestructure.WeekDay = RTC_WEEKDAY_TUESDAY;
	if (HAL_RTC_SetDate(&RtcHandle, &sdatestructure, RTC_FORMAT_BCD) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	/*##-2- Configure the Time #################################################*/
	/* Set Time: 02:20:00 */
//	stimestructure.Hours = 0x02;
//	stimestructure.Minutes = 0x20;
//	stimestructure.Seconds = 0x00;
//	stimestructure.TimeFormat = RTC_HOURFORMAT12_AM;
//	stimestructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
//	stimestructure.StoreOperation = RTC_STOREOPERATION_RESET;
	if (HAL_RTC_SetTime(&RtcHandle, &stimestructure, RTC_FORMAT_BCD) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	/*##-3- Configure the RTC Alarm peripheral #################################*/
	/* Set Alarm to 02:20:30
	 RTC Alarm Generation: Alarm on Hours, Minutes and Seconds */
	salarmstructure.Alarm = RTC_ALARM_A;
	salarmstructure.AlarmDateWeekDay = RTC_WEEKDAY_MONDAY;
	salarmstructure.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
	salarmstructure.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY;
	salarmstructure.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_NONE;
	salarmstructure.AlarmTime.TimeFormat = RTC_HOURFORMAT12_AM;
	salarmstructure.AlarmTime.Hours = 0x02;
	salarmstructure.AlarmTime.Minutes = 0x20;
	salarmstructure.AlarmTime.Seconds = 0x30;
	salarmstructure.AlarmTime.SubSeconds = 0x56;

	if (HAL_RTC_SetAlarm_IT(&RtcHandle, &salarmstructure, RTC_FORMAT_BCD) != HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}
}

/**
 * @brief  Display the current time.
 * @param  showtime : pointer to buffer
 * @retval None
 */
static void RTC_TimeShow(RTC_HandleTypeDef *RtcHandle, uint8_t* showtime) {
	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;

	/* Get the RTC current Time */
	HAL_RTC_GetTime(RtcHandle, &stimestructureget, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);
	/* Display time Format : hh:mm:ss */
	sprintf((char*) showtime, "%02d:%02d:%02d", stimestructureget.Hours, stimestructureget.Minutes,
			stimestructureget.Seconds);
}
