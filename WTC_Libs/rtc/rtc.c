/*
 * rtc.c
 *
 *  Created on: Apr 7, 2018
 *      Author: Administrator
 */

#include "rtc.h"

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
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, 0x08080000, time_32);
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD, 0x08080010, date_32);
		uint32_t data_time = *(uint32_t *) 0x08080000; //Read: Cast the address as a uint32_t pointer and dereference it
		uint32_t data_date = *(uint32_t *) 0x08080010; //Read: Cast the address as a uint32_t pointer and dereference it
		HAL_FLASHEx_DATAEEPROM_Lock(); //Lock when done? (Not sure if necessary)
	}

	HAL_Delay(10);
}
