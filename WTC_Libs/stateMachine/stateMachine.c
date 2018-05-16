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

WTCStatusStruct my_wtc;
WTCStatusStruct *wtc = &my_wtc;

void initWTCStatusStruct(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc,
		RTC_HandleTypeDef *hrtc, RTC_AlarmTypeDef *sAlarm) {

//INITIALIZE STRUCTS
	wtc->huartDebug = huart;
	wtc->hadc = hadc;
	wtc->hrtc = hrtc;
	wtc->sAlarm = sAlarm;

	wtc->deployStruct = deployStruct;
//RTC
	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;

	/* Get the RTC current Time */
	HAL_RTC_GetTime(hrtc, &stimestructureget, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(hrtc, &sdatestructureget, RTC_FORMAT_BIN);

	//Initial Date Alive
	wtc->startDate = sdatestructureget.Date;
	wtc->startMonth = sdatestructureget.Month;
	wtc->startYear = sdatestructureget.Year;
	//Initial Time Alive
	wtc->startHours = stimestructureget.Hours;
	wtc->startMinutes = stimestructureget.Minutes;
	wtc->startSeconds = stimestructureget.Seconds;

	//start deployment Alarm
	wtc->deployStruct->deployAlarmSet = FALSE;

}

/*****IMPORTANT*****
 * MUST CALL HAL_RTC_GetTime and HAL_RTC_GetDate together
 * or the RTC will not update!!!!
 */

void wtcSetup(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc, RTC_HandleTypeDef *hrtc,
		RTC_AlarmTypeDef *sAlarm) {

	putS(huart, "dp\r\n");
	wtc->deployStruct = initDeployStatusStruct();

	//setup function for WTC, 3.3v power is on
	// when disengaging from dispenser
	char prompt[100] = { };

	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;
	/* Get the RTC current Time */
	HAL_RTC_GetTime(hrtc, &stimestructureget, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(hrtc, &sdatestructureget, RTC_FORMAT_BIN);

	uint8_t sec = (stimestructureget.Seconds + wtc->deployStruct->deployWaitTimeMin) % 60;

	sprintf(prompt, "Will deploy at %d sec:", sec);
	putS(huart, prompt);
	printTime(huart, hrtc, sAlarm, 1);

	//wait XX minutes to deloy space craft
	while (sec != stimestructureget.Seconds) {
		/* Get the RTC current Time */
		HAL_RTC_GetTime(hrtc, &stimestructureget, RTC_FORMAT_BIN);
		/* Get the RTC current Date */
		HAL_RTC_GetDate(hrtc, &sdatestructureget, RTC_FORMAT_BIN);

		printTime(huart, hrtc, sAlarm, 0);
		HAL_Delay(200);
	}

	sprintf(prompt, "----DEPLOY----\r\n");
	putS(huart, prompt);

	//end of 'DEPLOY_WAIT_DELAY_MINS' timer, deploy antenna

	// turn on deployment rail enable
	//HAL_GPIO_TogglePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin);
	HAL_GPIO_WritePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin, GPIO_PIN_SET);
	//check_3v_status
	//deploy_antenna

	sprintf(prompt, "-- DP 1\r\n");
	putS(huart, prompt);
	writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_SET);
	HAL_Delay(5000);
	writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_RESET);

	sprintf(prompt, "-- End DP 1\r\n");
	putS(huart, prompt);
//	HAL_Delay(7000);

	sprintf(prompt, "-- DP 2\r\n");
	putS(huart, prompt);

	writeDPin(UHF_Deploy_2_GPIO_Port, UHF_Deploy_2_Pin, GPIO_PIN_SET);
	HAL_Delay(5000);
	writeDPin(UHF_Deploy_2_GPIO_Port, UHF_Deploy_2_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin,
			GPIO_PIN_RESET);
	sprintf(prompt, "-- End DP 2\r\n");
	putS(huart, prompt);

	HAL_RTC_DeactivateAlarm(hrtc, RTC_ALARM_A);
	sprintf(prompt, "----END DEPLOY----\r\n");
	putS(huart, prompt);
	for(;;){

	}
// end clayton
	uint8_t waitTime = 10;  //example 10 seconds
	//uint32_t _70cm_AUX_ADC_Channel = 25; //does a macro exist?

	do {

		//Power considerations

		if(determineNextAntenna(wtc) == 0){
			//uh oh, too many attempts to deploy.
		}
		//get deployment status (int)
		//deployAntenna returns -2,-1,0,1,2, or 3
		/*
		 * -2 - timeout
		 * -1 - voltage not in range (current implementation results in this never occuring
		 *  0 - ~0V read, no antenna deployed
		 *  1 - ~0.6V read. antenna #1 deployed
		 *  2 - ~1.6V read. antenna #2 deployed
		 *  3 - ~3.3V read/ both antennas deployed
		 */
		wtc->deployStruct->deployStatus = deployAntenna(huart, hadc, hrtc,
				wtc->deployStruct->deployCurrentAntAttempted, waitTime);
		//NOTE: status may return -1(voltage out of bounds) or -2(timeout)

		//update deployment status
		if (wtc->deployStruct->deployStatus == 1) {
			wtc->deployStruct->deployedAnt1 = TRUE;
		}
		if (wtc->deployStruct->deployStatus == 2) {
			wtc->deployStruct->deployedAnt2 = TRUE;
		}

		//Toggle between current antenna to deploy
		if (wtc->deployStruct->deployCurrentAntAttempted == 1) {
			wtc->deployStruct->deployAttemptsAnt1++;
			wtc->deployStruct->deployCurrentAntAttempted = 2;
		} else {
			wtc->deployStruct->deployAttemptsAnt2++;
			wtc->deployStruct->deployCurrentAntAttempted = 1;
		}

		//wait 10 seconds to try again, or to break
		HAL_Delay(10000);

	} while (wtc->deployStruct->deployedAnt1 == FALSE && wtc->deployStruct->deployedAnt2 == FALSE
			&& wtc->deployStruct->deployStatus != 3);

// turn off deployment rail enable
//	HAL_GPIO_TogglePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin);
	HAL_GPIO_WritePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin,
			GPIO_PIN_RESET);
	sprintf(prompt, "final");
	putS(huart, prompt);
	printDeploymentStatus(huart, wtc->deployStruct->deployStatus, " ");

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

void scienceInit() {

}
void operations() {

}
void commsLoop() {

}
void groundOps() {

}

