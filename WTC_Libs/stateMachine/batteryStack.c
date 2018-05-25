/*
 * batteryStack.c
 *
 *  Created on: May 16, 2018
 *      Author: Administrator
 */
#include "batteryStack.h"

BatteryStatusStruct my_batteryStruct;
BatteryStatusStruct *batteryStruct = &my_batteryStruct;

float checkBatteryVoltage(uint8_t nBat) {

	uint32_t channel;
	switch (nBat) {
	case (1):
		channel = V_Stack_1_Meas_Channel;
		break;
	case (2):
		channel = V_Stack_2_Meas_Channel;
		break;
	case (3):
		channel = V_Stack_3_Meas_Channel;
		break;
	case (4):
		channel = V_Stack_4_Meas_Channel;
		break;
	default:
		return 0.0f;
	}

	return adcReadSingle(channel);
}

uint8_t isBatteryStackGood() {

	/*
	 * remove before flight
	 */

	uint8_t deploycode = DEPLOYACCESSCODE;
	if (deploycode != 1687) {
		return 4;
	}

	//continue
	batteryStruct->minThreshold = 5.8f; //see battery struct (mystructTypeDef header file.)
	batteryStruct->workingStacks = 4; //1-4
	// first check battery stack voltages
	if (adcReadSingle(V_Stack_1_Meas_Channel) < batteryStruct->minThreshold) {
		batteryStruct->battery1_PGOOD = FALSE;
		batteryStruct->workingStacks--;
	} else {
		batteryStruct->battery1_PGOOD = TRUE;
	}
	if (adcReadSingle(V_Stack_2_Meas_Channel) < batteryStruct->minThreshold) {
		batteryStruct->battery2_PGOOD = FALSE;
		batteryStruct->workingStacks--;
	} else {
		batteryStruct->battery2_PGOOD = TRUE;
	}
	if (adcReadSingle(V_Stack_3_Meas_Channel) < batteryStruct->minThreshold) {
		batteryStruct->battery3_PGOOD = FALSE;
		batteryStruct->workingStacks--;
	} else {
		batteryStruct->battery3_PGOOD = TRUE;
	}
	if (adcReadSingle(V_Stack_4_Meas_Channel) < batteryStruct->minThreshold) {
		batteryStruct->battery4_PGOOD = FALSE;
		batteryStruct->workingStacks--;
	} else {
		batteryStruct->battery4_PGOOD = TRUE;
	}

	// necessary for program execution
	// 1 battery stack 	- transceiver, pi's,wtc
	// 2 battery stacks 	- experiment
	return batteryStruct->workingStacks;
}

