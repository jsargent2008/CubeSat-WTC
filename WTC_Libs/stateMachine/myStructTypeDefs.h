/*
 * myStructTypeDefs.h
 *
 *  Created on: May 9, 2018
 *      Author: Theodore Cox
 */

#ifndef STATEMACHINE_MYSTRUCTTYPEDEFS_H_
#define STATEMACHINE_MYSTRUCTTYPEDEFS_H_

#include "main.h"
#include "usart.h"
#include "rtc.h"
#include "adc.h"
#include "stateMachine.h"

typedef struct BatteryStatusStruct {
	// if battery rail is a combination of all voltage stacks
	// battery rail threshold 5.2V, 5.8 before combining diodes
	// endrosat can only operate with battery rail above 5.2

	// experiment needs two available battery rails.
	float minThreshold;
	uint8_t battery1_V;
	uint8_t battery2_V;
	uint8_t battery3_V;
	uint8_t battery4_V;

	uint8_t workingStacks;
	uint8_t battery1_PGOOD;
	uint8_t battery2_PGOOD;
	uint8_t battery3_PGOOD;
	uint8_t battery4_PGOOD;

} BatteryStatusStruct;

extern BatteryStatusStruct * batteryStruct;

typedef struct DeployStatusStruct {

	//deployment
	uint8_t deployReady; 				// T or F
	uint8_t waitTimeMin;
	uint8_t deployAttemptTimeMaxSec;
	uint8_t deployedAnt1;				// T or F
	uint8_t deployedAnt2;				// T or F
	uint8_t deployAttemptsAnt1;
	uint8_t deployAttemptsAnt2;
	uint8_t deployDenyAnt1; 			// T or F
	uint8_t deployDenyAnt2; 			// T or F
	uint8_t deployMaxAttemptsPer;		//2?
	uint8_t deployMaxAttemptsTotal;		//2?
	uint8_t deployCurAntAttempted;
	uint8_t deployStatus; // -1,0,1,2,or 3 IMPORTANT: deployStatus should be able to be overwritten if comms is successful to and from ground, regardless of the deployment sense voltage.
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
