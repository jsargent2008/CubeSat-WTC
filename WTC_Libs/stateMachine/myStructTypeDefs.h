/*
 * myStructTypeDefs.h
 *
 *  Created on: May 9, 2018
 *      Author: Theodore Cox
 */

#ifndef STATEMACHINE_MYSTRUCTTYPEDEFS_H_
#define STATEMACHINE_MYSTRUCTTYPEDEFS_H_

#include "main.h"

typedef struct DeployStatusStruct {

	//deployment
	uint8_t deployReady; 				// T or F
	uint8_t deployWaitTimeMin;
	uint8_t deployAttemptTimeMaxSec;
	uint8_t deployedAnt1;				// T or F
	uint8_t deployedAnt2;				// T or F
	uint8_t deployAttemptsAnt1;
	uint8_t deployAttemptsAnt2;
	uint8_t deployDenyAnt1; 			// T or F
	uint8_t deployDenyAnt2; 			// T or F
	uint8_t deployMaxAttemptsPer;
	uint8_t deployMaxAttemptsTotal;
	uint8_t deployCurrentAntAttempted;
	uint8_t deployStatus;
	float deploySenseV;

	// initial date-time deployed
	uint8_t deployDate;
	uint8_t deployMonth;
	uint8_t deployYear;
	uint8_t deployHours;
	uint8_t deployMinutes;
	uint8_t deploySeconds;
	uint8_t deployAlarmSet;

} DeployStatusStruct;

extern DeployStatusStruct *deployStruct;

typedef struct WTCStatusStruct {

//SYSTEM STRUCTS:
	UART_HandleTypeDef *huartDebug;
	ADC_HandleTypeDef *hadc;
	RTC_HandleTypeDef *hrtc;
	RTC_AlarmTypeDef *sAlarm;
//USER STRUCTS:
	DeployStatusStruct *deployStruct;

//MEMBER VARIABLES:
	//RTC (include members for date and time of 'alive' and 'deployed')
	//initial date-time alive
	uint8_t startDate;
	uint8_t startMonth;
	uint8_t startYear;
	uint8_t startHours;
	uint8_t startMinutes;
	uint8_t startSeconds;

//status word...

} WTCStatusStruct;

extern WTCStatusStruct *wtc;


#endif /* STATEMACHINE_MYSTRUCTTYPEDEFS_H_ */
