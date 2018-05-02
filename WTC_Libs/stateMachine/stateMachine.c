/*
 * stateMachine.c
 *
 *  Created on: Apr 27, 2018
 *      Author: Administrator
 */

//WTC Software Flow:
//------------------
//Initialization
//Deployed Signal
//Wait 30 minutes/check 3.3V
//Deploy Antennas (Ant x2, LP?)
//Confirm Deployed Antennas
//Battery Check
//Initial Comm (or Repeat Comms)
//Turn on Xceiver
//Listen
//Get Signal
//Send back "Hello Earth!" w/ Status
//Battery Check
//Operations
//Initialize w/checkout
//Science stack health (Pi health/Langmuir/Electrometer/Pico (x2 if failed))
//Good health - run default science check ADC & LP
//Bad Health no science check/send to SD card
//Science Health send to WTC SD card - transmit
//Shutdown unit
//Transmit
//Listen
//Contact/receive commands
//Send Spacecraft Health header (level 0) -13 bits
//Send Pi data packet(s)
//(comms protocols)
//Ground
//Building Orbit Model
//Establishing Comms windows
//Data on solar orientation model of spin/charging
//Science Ops
//Enable Pi
//Update run parameters and/or health check
//RUN (~15 mins)
//Science
//Collect points and create data packets
//Interrupt to shutdown or send data to WTC/SD

#include "stateMachine.h"

void wtcSetup(ADC_HandleTypeDef *hadc) {
	//setup function for WTC, 3.3v power is on
	// when disengaging from dispenser

	// RTC delay 30min

	//check_3v_status
	//deploy_antenna

	uint8_t deployStatus = depolyAntenna(hadc, 1);

	//check deployment of antenna

	//while(deployment == no){
	// decrement count. ex. try 10 times,...
	//delay_wait_time
	//deploy_antenna
	//}

	// turn_on_xceiver
	// listen
	// get_signal
	// print('Hello Earth!' + status)
	// check_battery
}

uint8_t depolyAntenna(ADC_HandleTypeDef *hadc, uint8_t antenna) {
	uint8_t status = 0;

	//deployAntenna

	//UHF_Power_Enable
	//Deployment_Power_Enable

	writeDPin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin, GPIO_PIN_SET);
	HAL_Delay(10);
	//UHF_Deploy_1
	uint32_t _70cm_AUX_ADC_Channel = 25; //does a macro exist?
	float dplyV = adcReadSingle(hadc, _70cm_AUX_ADC_Channel);
	//dplyV ex --> 3.3V
	uint8_t thresholdV;
	if (antenna == 1) {
		writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_SET);
		thresholdV = 0.6;
	} else if (antenna == 2) {
		writeDPin(UHF_Deploy_2_GPIO_Port, UHF_Deploy_2_Pin, GPIO_PIN_SET);
		thresholdV = 1.7;
	} else
		return 0;

	uint8_t dplyStatus = deploymentSense(hadc, antenna, thresholdV, dplyV);
	writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_RESET);
	//deployment sense
	uint8_t dplySense = readDPin(_70cm_AUX_ADC_GPIO_Port, _70cm_AUX_ADC_Pin);

	//UHF_Deploy_2

	status = 1;
	return status;
}

uint8_t deploymentSense(ADC_HandleTypeDef *hadc, uint8_t antenna, uint8_t thresholdV, float dplyV) {
	//Deployment sense
	//test threshold at
	// 	3.3V for no deployment.
	//	1.7V for deployment 1 (individually).
	// 	0.6V for deployment 2 (individually).
	// 	0.0V for both deployed.
	uint32_t _70cm_AUX_ADC_Channel = 25; //does a macro exist?

	float currDplyV = dplyV;
	// threshold of 60% of 3.3V is ~2V
	//abritrary until hardware tested

	uint16_t tick = 0;
	do {
		HAL_Delay(10);
		tick++;
		currDplyV = adcReadSingle(hadc, _70cm_AUX_ADC_Channel);
		if (dplyV - currDplyV > thresholdV)
			return antenna;

	} while (tick < 1000); //10 second delay limit

	//if no deployment sensed return 0
	return 0;
}

void scienceInit() {

}
void operations() {

}
void commsLoop() {

}
void groundOps() {

}

