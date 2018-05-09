/*
 * stateMachine.h
 *
 *  Created on: Apr 27, 2018
 *      Author: Administrator
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


//function prototypes

void wtcSetup(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc, RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm);
int8_t deployAntenna(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc, RTC_HandleTypeDef *hrtc, uint8_t nAntenna, uint8_t waitTime);
int8_t deploymentSense(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc, float tolerance);
void printDeploymentStatus(UART_HandleTypeDef *huart, int8_t status, char* tabs);
void commsLoop();
void groundOps();
void scienceInit();
void operations();

//uint8_t DEPLOYMENT_STATUS_BYTE;  might be useful

#include "stateMachine.c"
#endif /* STATEMACHINE_STATEMACHINE_H_ */
