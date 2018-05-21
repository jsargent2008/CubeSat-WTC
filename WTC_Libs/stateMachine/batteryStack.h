/*
 * batteryStack.h
 *
 *  Created on: May 16, 2018
 *      Author: Administrator
 */

#ifndef STATEMACHINE_BATTERYSTACK_H_
#define STATEMACHINE_BATTERYSTACK_H_

#include "myStructTypeDefs.h"
#include "stateMachine.h"

#define V_Stack_1_Meas_Channel 12
#define V_Stack_2_Meas_Channel 13
#define V_Stack_3_Meas_Channel 14
#define V_Stack_4_Meas_Channel 15

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

	return adcReadSingle(hadc, channel);
}

uint8_t updateFlagBattery(uint8_t nBat){
	uint8_t status = 0;
	uint8_t voltage = checkBatteryVoltage(nBat);
	switch(nBat){
	case(1):
			batteryStruct->battery1_V = voltage;
		break;
	case(2):
			batteryStruct->battery1_V = voltage;
		break;
	case(3):
		batteryStruct->battery1_V = voltage;
		break;
	case(4):
		batteryStruct->battery1_V = voltage;
		break;
	default:
		break;
	}
	if(voltage == )

}

#endif /* STATEMACHINE_BATTERYSTACK_H_ */
