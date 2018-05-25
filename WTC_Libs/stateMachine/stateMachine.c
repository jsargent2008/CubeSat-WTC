/*
 * stateMachine.c
 *
 *  Created on: Apr 27, 2018
 *      Author: Administrator
 */

#define DEPLOY_WAIT_DELAY_SEC 10

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

//WTCStatusStruct my_wtc;
//WTCStatusStruct *wtc = &my_wtc;

/*****IMPORTANT*****
 * MUST CALL HAL_RTC_GetTime and HAL_RTC_GetDate together
 * or the RTC will not update!!!!
 */

void wtcSetup() {

	char prompt[100] = { };
	//putS(&DEBUG_UART, "dp\r\n");
	initWTCStatusStruct();
	initDeployStatusStruct();

	//setup function for WTC, 3.3v power is on
	// when disengaging from dispenser
	//attempt to deploy
	uint8_t attempt = 0;
	int8_t deployStatus = 0;
	uint8_t antenna = 0;
	do {
		//1 hour wait timer compressed into the function below
		waitToDeploy(attempt);
		if(isBatteryStackGood() > 0){
			deployStatus = deploySimple(antenna + 1);
			antenna ^= 1; //toggle between atenna 1 & 2
		}
		// end of 'DEPLOY_WAIT_DELAY_MINS' timer, deploy antenna
		// ALSO break if communication has been received by ground.
		attempt++;

		if(deployStruct->deployedAnt1 == true && deployStruct->deployedAnt2 == false){
			break;
		}
	} while (deployStatus != 3);

	sprintf(prompt, "--Antennas Deployed--\r\n");
	putS(&DEBUG_UART, prompt);

	// turn_on_xceiver
	for (;;) {
	// listen, break when RX buffer full
	}

	// get_signal

	// print('Hello Earth!' + status)
	// check_battery
}

void scienceInit() {

}

void operations() {

}

