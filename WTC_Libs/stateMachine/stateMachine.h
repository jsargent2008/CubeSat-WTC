/*
 * stateMachine.h
 *
 *  Created on: Apr 27, 2018
 *      Author: Theodore Cox
 */

#ifndef STATEMACHINE_STATEMACHINE_H_
#define STATEMACHINE_STATEMACHINE_H_

//includes
#include <myadc/myadc.h>
#include <mygpio/mygpio.h>
#include <myrtc/myrtc.h>
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "float.h"
#include "math.h"
#include "UART_IRQ/UART_IRQ.h"
#include "deployment.h"
#include "myStructTypeDefs.h"

//function prototypes

void initWTCStatusStruct(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc,
		RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm);
void wtcSetup(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc, RTC_HandleTypeDef *hrtc,
		RTC_AlarmTypeDef *sAlarm);
void commsLoop();
void groundOps();
void scienceInit();
void operations();
void stateMachine_RTC_AlarmA();

#include "stateMachine.c"
#endif /* STATEMACHINE_STATEMACHINE_H_ */
