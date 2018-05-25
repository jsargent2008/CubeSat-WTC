/*
 * batteryStack.h
 *
 *  Created on: May 16, 2018
 *      Author: Administrator
 */

#ifndef STATEMACHINE_BATTERYSTACK_H_
#define STATEMACHINE_BATTERYSTACK_H_
//#include "main.h"
#include "myStructTypeDefs.h"
#include "stateMachine.h"

#define V_Stack_1_Meas_Channel 12
#define V_Stack_2_Meas_Channel 13
#define V_Stack_3_Meas_Channel 14
#define V_Stack_4_Meas_Channel 15

float checkBatteryVoltage(uint8_t nBat);

// use 'isBatteryStackGood' inside of the rtc alarm 10sec tick function
// check return value to determine if enough battery stacks are available to
// be used.
uint8_t isBatteryStackGood();

#endif /* STATEMACHINE_BATTERYSTACK_H_ */
