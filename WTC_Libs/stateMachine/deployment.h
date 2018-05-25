/*
 * deployment.h
 *
 *  Created on: May 9, 2018
 *      Author: Theodore Cox
 */

#ifndef STATEMACHINE_DEPLOYMENT_H_
#define STATEMACHINE_DEPLOYMENT_H_

#define ADC_Channel_70cm_AUX 25
#include "main.h"
#include "myStructTypeDefs.h"
#include "stateMachine.h"

//function prototypes
/*
 * AS of 5-22-18 use deploySimple(in conjunction with deploymentSense and deploymentStatusStruct to deploy antennas)
 */
void initDeployStatusStruct();
int8_t deploymentSense(float tolerance);

int8_t deploySimple(uint8_t deplyAntNum);

int8_t deploy();
int8_t deployHelper();
uint8_t waitToDeploy(uint8_t attempt);
void printDeploymentStatus(int8_t status, char* tabs);

uint8_t determineNextAntenna();
int8_t deployAntenna(uint8_t nAntenna, uint8_t waitTime);
#endif /* STATEMACHINE_DEPLOYMENT_H_ */
