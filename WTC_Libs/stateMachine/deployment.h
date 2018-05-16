/*
 * deployment.h
 *
 *  Created on: May 9, 2018
 *      Author: Theodore Cox
 */

#ifndef STATEMACHINE_DEPLOYMENT_H_
#define STATEMACHINE_DEPLOYMENT_H_

#define TRUE 1
#define FALSE 0
#define True 1
#define False 0

#include "myStructTypeDefs.h"
#include "stateMachine.h"



//function prototypes
DeployStatusStruct *initDeployStatusStruct();
uint8_t determineNextAntenna();
int8_t deployAntenna(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc, RTC_HandleTypeDef *hrtc,
		uint8_t nAntenna, uint8_t waitTime);
int8_t deploymentSense(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc, float tolerance);
void printDeploymentStatus(UART_HandleTypeDef *huart, int8_t status, char* tabs);

#endif /* STATEMACHINE_DEPLOYMENT_H_ */
