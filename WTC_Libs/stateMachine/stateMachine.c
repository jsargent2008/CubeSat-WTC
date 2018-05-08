/*
 * stateMachine.c
 *
 *  Created on: Apr 27, 2018
 *      Author: Administrator
 */

#define DEPLOY_WAIT_DELAY_SEC 10
#define TRUE 1
#define FALSE 0

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

/*****IMPORTANT*****
 * MUST CALL HAL_RTC_GetTime and HAL_RTC_GetDate together
 * or the RTC will not update!!!!
 */

void wtcSetup(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc, RTC_HandleTypeDef *hrtc,
		RTC_AlarmTypeDef *sAlarm) {

	putS(huart, "dp\r\n");

	//setup function for WTC, 3.3v power is on
	// when disengaging from dispenser
	char prompt[100] = { };
	// RTC delay 30min
	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;

	/* Get the RTC current Time */
	HAL_RTC_GetTime(hrtc, &stimestructureget, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(hrtc, &sdatestructureget, RTC_FORMAT_BIN);

	uint8_t sec = (stimestructureget.Seconds + DEPLOY_WAIT_DELAY_SEC) % 60;
	sprintf((char*) prompt, "Deploy at:\t\t%02d:%02d:%02d\r\n", stimestructureget.Hours,
			stimestructureget.Minutes, sec);
	putS(huart, prompt);

	while (sec != stimestructureget.Seconds) {
		HAL_RTC_GetTime(hrtc, &stimestructureget, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(hrtc, &sdatestructureget, RTC_FORMAT_BIN);
//
		//print to UART
		sprintf((char*) prompt, "Current Time:\t\t%02d:%02d:%02d\r", stimestructureget.Hours,
				stimestructureget.Minutes, stimestructureget.Seconds);
		putS(huart, prompt);

		HAL_Delay(200);
	}

	sprintf((char*) prompt, "\r\n");
	putS(huart, prompt);

	//end of 'DEPLOY_WAIT_DELAY_MINS' timer, deploy antenna

	// turn on deployment rail enable
	//HAL_GPIO_TogglePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin);
	HAL_GPIO_WritePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin, GPIO_PIN_SET);
	//check_3v_status
	//deploy_antenna
	uint8_t ant1_nAttempts = 0;
	uint8_t ant2_nAttempts = 0;
	uint8_t nAttempts = 0;
	int8_t nAntenna = 1;
	int8_t deployStatus = 0;
	uint8_t waitTime = 10;  //example 10 seconds
	uint32_t _70cm_AUX_ADC_Channel = 25; //does a macro exist?

	uint8_t ant1_hasBeenDeployed = FALSE;
	uint8_t ant2_hasBeenDeployed = FALSE;
	uint8_t changeAnt = FALSE;
	uint8_t loopLimit = 10;
	uint8_t attemptsLimit = 1;
	do {
		loopLimit--;
		//get deployment status (int)
		deployStatus = deployAntenna(huart, hadc, hrtc, nAntenna, waitTime);

		if (nAntenna == 1) {
			ant1_nAttempts++;
		}
		if (nAntenna == 2) {
			ant1_nAttempts++;
		}

		if (deployStatus == 1 && ant1_hasBeenDeployed == FALSE) {
			ant1_hasBeenDeployed = TRUE;
			changeAnt = TRUE;
		}
		if (deployStatus == 2 && ant2_hasBeenDeployed == FALSE) {
			ant2_hasBeenDeployed = TRUE;
			changeAnt = TRUE;
		}

		nAttempts++;
		if (nAttempts >= attemptsLimit || changeAnt == TRUE) {
			changeAnt = FALSE;
			if (nAntenna == 1 && ant2_hasBeenDeployed == FALSE) {
				nAntenna = 2;
			} else if (nAntenna == 2 && ant1_hasBeenDeployed == FALSE) {
				nAntenna = 1;
			}
		}

		if (ant1_nAttempts >= attemptsLimit) {
			nAntenna = 2;
			if (ant2_nAttempts >= attemptsLimit) {
				break;
			}
		} else if (ant2_nAttempts >= attemptsLimit) {
			nAntenna = 1;
			if (ant1_nAttempts >= attemptsLimit) {
				break;
			}
		}
		if (ant1_hasBeenDeployed == TRUE && ant2_hasBeenDeployed == TRUE) {
			deployStatus = 3;
		}
		//NOTE: status may return -1(voltage out of bounds) or -2(timeout)

	} while (deployStatus != 3 && loopLimit > 0);

	// turn off deployment rail enable
//	HAL_GPIO_TogglePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin);
	HAL_GPIO_WritePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin,
			GPIO_PIN_RESET);
	sprintf(prompt, "final");
	putS(huart, prompt);
	printDeploymentStatus(huart, deployStatus, " ");

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

void printDeploymentStatus(UART_HandleTypeDef *huart, int8_t status, char* tabs) {
	char prompt[100] = { };
	if (status == -2) {
		sprintf(prompt, "%s status: %d. Deployment sense timeout.\r\n", tabs, status);
	} else if (status == -1) {
		sprintf(prompt, "%s status: %d. Deployment sense voltage read error.\r\n", tabs, status);
	} else if (status == 0) {
		sprintf(prompt, "%s status: %d. No antennas deployed\r\n", tabs, status);
	} else if (status == 1) {
		sprintf(prompt, "%s status: %d. Only antenna #1 deployed.\r\n", tabs, status);
	} else if (status == 2) {
		sprintf(prompt, "%s status: %d. Only antenna #2 deployed.\r\n", tabs, status);
	} else {
		sprintf(prompt, "%s status: %d. Both antennas deployed.\r\n", tabs, status);
	}
	putS(huart, prompt);
}

int8_t deployAntenna(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc, RTC_HandleTypeDef *hrtc,
		uint8_t nAntenna, uint8_t waitTime) {

	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;

	char prompt[100] = { };
//deployAntenna
//UHF_Power_Enable
//Deployment_Power_Enable
	//writeDPin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin, GPIO_PIN_SET);
	//HAL_Delay(10);

	int8_t status;	// = deploymentSense(huart, hadc, 0.0f);
	uint8_t wantedStatus;
	if (nAntenna == 1) {
		writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_SET);
		wantedStatus = 1;
	} else {
		writeDPin(UHF_Deploy_2_GPIO_Port, UHF_Deploy_2_Pin, GPIO_PIN_SET);
		wantedStatus = 2;
	}

	float tolerance = 0.20f;
	uint8_t _70cm_AUX_ADC_Channel = 25;

	/* Get the RTC current Time */
	HAL_RTC_GetTime(hrtc, &stimestructureget, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(hrtc, &sdatestructureget, RTC_FORMAT_BIN);

	//example - waitTime = 10 seconds
	uint8_t sec = (stimestructureget.Seconds + waitTime) % 60;
	uint8_t tempS = stimestructureget.Seconds;
	do {
		status = deploymentSense(huart, hadc, tolerance);

		/* Get the RTC current Time */
		HAL_RTC_GetTime(hrtc, &stimestructureget, RTC_FORMAT_BIN);
		/* Get the RTC current Date */
		HAL_RTC_GetDate(hrtc, &sdatestructureget, RTC_FORMAT_BIN);
		uint8_t curSec = stimestructureget.Seconds;
		//print to UART
//		sprintf(prompt, "\t\tstatus: %d\r\n", status);
//		putS(huart, prompt);

		//print to UART
		sprintf(prompt, "deploy: %d, status: %d, reading %f V, On for %d seconds...\r", (int) nAntenna,
				(int) (status),
				adcReadSingle(hadc, _70cm_AUX_ADC_Channel), abs(curSec - tempS) % 60);
		putS(huart, prompt);

		HAL_Delay(200);

		//timeout
		if (sec < curSec) {
			//status = -2;
			break;
		}
	} while (status != wantedStatus && status != 3);

	sprintf(prompt, "\r\n");
	putS(huart, prompt);
	writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_RESET);
	writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_2_Pin, GPIO_PIN_RESET);
	HAL_Delay(100);
	return status;

//UHF_Deploy_1

//	uint8_t thresholdV;
//	if (antenna == 1) {
//		writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_SET);
//		thresholdV = 0.6;
//	} else if (antenna == 2) {
//		writeDPin(UHF_Deploy_2_GPIO_Port, UHF_Deploy_2_Pin, GPIO_PIN_SET);
//		thresholdV = 1.7;
//	} else
//		return 0;
//
//	uint8_t dplyStatus = deploymentSense(hadc, antenna, thresholdV, dplyV);
//	writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_RESET);
//	//deployment sense
//	uint8_t dplySense = readDPin(_70cm_AUX_ADC_GPIO_Port, _70cm_AUX_ADC_Pin);
//
//	//UHF_Deploy_2
//
//	status = 1;
//	return status;
}

/*
 * returns switch antenna has been deployed
 */
int8_t deploymentSense(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc, float tolerance) {
//char prompt[100] = { };
//Deployment sense
//test threshold at
// 	0.0V for no deployment.
// 	0.6V for deployment 1 (individually).
//	1.65V for deployment 2 (individually).
// 	3.3V for both deployed.

	HAL_Delay(100);

	uint32_t _70cm_AUX_ADC_Channel = 25; //does a macro exist?
	float dplyV = adcReadSingle(hadc, _70cm_AUX_ADC_Channel);

//print to UART
//	sprintf(prompt, "sense: %f V\r\n", dplyV);
//	putS(huart, prompt);

//dplyV start ex --> 0.0V
	float deployedNone = 0.0f;
	float deployed1 = 0.66f;
	float deployed2 = 1.65f;
	float deployedAll = 3.3f;

	if (tolerance < 0.20f || tolerance > 0.40f) {
		tolerance = 0.20f; // 0.20 tolerance
	}

	if (dplyV >= deployedNone - tolerance && dplyV < deployed1 - tolerance) {
		// 0 antennas deployed
		return 0;
	} else if (dplyV >= deployed1 - tolerance && dplyV < deployed2 - tolerance) {
		// antenna #1 deployed
		return 1;
	} else if (dplyV >= deployed2 - tolerance && dplyV < deployedAll - tolerance) {
		// antenna #2 deployed
		return 2;
	} else if (dplyV >= deployedAll - tolerance) {
		// antenna #1 & #2 deployed
		return 3;
	} else {
		// nothing sensed, adjust voltage reading tolerance by 0.10
		return -1;
	}
}

void scienceInit() {

}
void operations() {

}
void commsLoop() {

}
void groundOps() {

}

