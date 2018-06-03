#include "deployment.h"

DeployStatusStruct my_deployStruct;
DeployStatusStruct *deployStruct = &my_deployStruct;

void initDeployStatusStruct() {
	DeployStatusStruct *deployStruct = malloc(sizeof(DeployStatusStruct));
	deployStruct->waitTimeMin = 45;
	deployStruct->deployAttemptTimeMaxSec = 10;
	deployStruct->deployMaxAttemptsPer = 2;
	deployStruct->deployMaxAttemptsTotal = 4;
	deployStruct->deployCurAntAttempted = 0;
	deployStruct->deployedAnt1 = false;
	deployStruct->deployedAnt2 = false;
	deployStruct->deployAttemptsAnt1 = 0;
	deployStruct->deployAttemptsAnt2 = 0;
	deployStruct->deployStatus = 0;
	deployStruct->deploySenseV = 0.0f;

}

/*
 * Call deploySimple initially once. If the return value is not 3 (meaning both antennas are
 */
int8_t deploySimple(uint8_t deplyAntNum) {

	char prompt[100] = { };

	if (DEPLOYACCESSCODE != 1687) {
		sprintf(prompt, "DEPLOYACCESSCODE IS 1687\r\n");
		putS(&DEBUG_UART, prompt);
		return 3;

	} else {
		//enable deployment rail
		HAL_GPIO_WritePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin,
				GPIO_PIN_SET);
		HAL_Delay(1000);

		if (deplyAntNum == 1 && DEPLOYACCESSCODE == 1687) {
			writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_SET);
			HAL_Delay(1000);
		} else if (deplyAntNum == 2 && DEPLOYACCESSCODE == 1687) {
			writeDPin(UHF_Deploy_2_GPIO_Port, UHF_Deploy_2_Pin, GPIO_PIN_SET);
			HAL_Delay(1000);
		}
	}
	HAL_GPIO_WritePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin,
			GPIO_PIN_RESET);
	writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_RESET);
	writeDPin(UHF_Deploy_2_GPIO_Port, UHF_Deploy_2_Pin, GPIO_PIN_RESET);

	return deploymentSense(0.20f);

}

int8_t deploy() {
	if (batteryStruct->workingStacks > 1) {
		return deployHelper();
	}

	return -2;
}
int8_t deployHelper() {

	char prompt[100] = { };
	//while battery status good!!! <- don't forget to implement
	int8_t sense = deploymentSense(0.20f);
	int8_t attempts = 0;

	//enable deployment rail
	HAL_GPIO_WritePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin, GPIO_PIN_SET);

	/*
	 * ***ANTENNA 1***
	 */
	//check to see if antenna #1 has already been deployed before entering while-loop (STATUS BIT)
	while (deployStruct->deployedAnt1 != true) {

		sprintf(prompt, "-- DP 1\r\n");
		putS(&DEBUG_UART, prompt);

		deployStruct->deployCurAntAttempted = 1;
		writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_SET);
		//break if a voltage change is sensed on the deployment line
		if (sense != deploymentSense(0.20f)) {
			break;
		} else if (attempts == 2) {
			break;
		}
		attempts++;
		//turn off
		HAL_Delay(1000);

		sprintf(prompt, "-- End DP 1\r\n");
		putS(&DEBUG_UART, prompt);

		writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_RESET);
		HAL_Delay(1000);
	}

	sprintf(prompt, "-- End DP 1\r\n");
	putS(&DEBUG_UART, prompt);

	writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_RESET);
	deployStruct->deployCurAntAttempted = 0;
	HAL_Delay(1000);

	/*
	 * ***ANTENNA 2***
	 */
	attempts = 0;
	//check to see if antenna #2 has already been deployed before entering while-loop (STATUS BIT)
	while (deployStruct->deployedAnt2 != true) {

		sprintf(prompt, "-- DP 2\r\n");
		putS(&DEBUG_UART, prompt);

		deployStruct->deployCurAntAttempted = 2;
		writeDPin(UHF_Deploy_2_GPIO_Port, UHF_Deploy_2_Pin, GPIO_PIN_SET);
		//break if a voltage change is sensed on the deployment line
		if (sense != deploymentSense(0.20f)) {
			break;
		} else if (attempts == 2) {
			break;
		}
		attempts++;
		//turn off
		HAL_Delay(1000);

		sprintf(prompt, "-- End DP 2\r\n");
		putS(&DEBUG_UART, prompt);

		writeDPin(UHF_Deploy_2_GPIO_Port, UHF_Deploy_2_Pin, GPIO_PIN_RESET);
		HAL_Delay(1000);
	}

	sprintf(prompt, "-- End DP 2\r\n");
	putS(&DEBUG_UART, prompt);

	writeDPin(UHF_Deploy_2_GPIO_Port, UHF_Deploy_2_Pin, GPIO_PIN_RESET);
	deployStruct->deployCurAntAttempted = 0;

	//disable deployment rail
	HAL_GPIO_WritePin(Deployment_Power_Enable_GPIO_Port, Deployment_Power_Enable_Pin,
			GPIO_PIN_RESET);

	/*
	 * status -
	 * 			0 - no antennas deployed
	 * 			1 - antenna 1 deployed
	 * 			2 - antenna 2 deployed
	 * 			3 - antennas 1 & 2 deployed
	 */
	return deployStruct->deployStatus;
}
/*
 * returns switch antenna has been deployed
 */
int8_t deploymentSense(float tolerance) {
//char prompt[100] = { };
//Deployment sense
//test threshold at
// 	0.0V for no deployment.
// 	0.6V for deployment 1 (individually).
//	1.65V for deployment 2 (individually).
// 	3.3V for both deployed.

	HAL_Delay(10);

	//uint32_t _70cm_AUX_ADC_Channel = 25; //does a macro exist?
	float dplyV = adcReadSingle(ADC_Channel_70cm_AUX);

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
		deployStruct->deployedAnt1 = true;
		deployStruct->deployStatus = 1;
		return 1;
	} else if (dplyV >= deployed2 - tolerance && dplyV < deployedAll - tolerance) {
		// antenna #2 deployed
		deployStruct->deployedAnt2 = true;
		deployStruct->deployStatus = 2;
		return 2;
	} else if (dplyV >= deployedAll - tolerance) {
		// antenna #1 & #2 deployed
		deployStruct->deployedAnt1 = true;
		deployStruct->deployedAnt2 = true;
		deployStruct->deployStatus = 3;
		return 3;
	} else {
		// nothing sensed, adjust voltage reading tolerance by 0.10
		return -1;
	}
}

uint8_t waitToDeploy(uint8_t attempt) {

	char prompt[100] = { };
	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;
	/* Get the RTC current Time */
	HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);

	uint8_t waitMin = 59;
	uint8_t mins = (stimestructureget.Minutes + waitMin) % 60;
	uint8_t minsActual = stimestructureget.Minutes;

	//wait XX minutes to deploy space craft
	while (mins != minsActual) {
		/* Get the RTC current Time */
		HAL_RTC_GetTime(&hrtc, &stimestructureget, RTC_FORMAT_BIN);
		/* Get the RTC current Date */
		HAL_RTC_GetDate(&hrtc, &sdatestructureget, RTC_FORMAT_BIN);

//			if(minsActual != stimestructureget.Minutes){
		sprintf(prompt, "T-Minus %02d:%02d until deployment\r", waitMin + (mins - minsActual),
				59 - stimestructureget.Seconds);
		putS(&DEBUG_UART, prompt);
//			}
		minsActual = stimestructureget.Minutes;

		HAL_Delay(200);
	}
	sprintf(prompt, "\r\n");
	putS(&DEBUG_UART, prompt);

	sprintf(prompt, "----ATTEMPT TO DEPLOY----\r\n");
	putS(&DEBUG_UART, prompt);

	return 0;
}

void secureDeploy(uint8_t antenna) {

}

void printDeploymentStatus(int8_t status, char* tabs) {
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
	putS(&DEBUG_UART, prompt);
}

//uint8_t determineNextAntenna(WTCStatusStruct *wtc) {
//	//Check if the max deployment attempts for the antennas as been reached.
//	uint8_t nextAntennaDetermined = FALSE;
//	uint8_t infinitLoopFlag = RESET;
//	while (nextAntennaDetermined == FALSE) {
//		nextAntennaDetermined = TRUE;
//
//		//if ant1 is still available to attempt to deploy
//		if (wtc->deployStruct->deployCurAntAttempted == 1) {
//			//if ant1 HASN'T been denied yet
//			if (wtc->deployStruct->deployDenyAnt1 == FALSE) {
//				//if ant1 is over the max attempts allowed
//				if (wtc->deployStruct->deployAttemptsAnt1
//						> wtc->deployStruct->deployMaxAttemptsPer) {
//					wtc->deployStruct->deployDenyAnt1 = TRUE;
//				}
//			}
//			//if ant1 HAS been denied
//			if (wtc->deployStruct->deployDenyAnt1 == TRUE) {
//				nextAntennaDetermined = FALSE;
//				// if switching antennas has already been attempted and unsuccessful
//				if (infinitLoopFlag == SET) {
//					break;
//				} else {
//					infinitLoopFlag = SET;
//				}
//				wtc->deployStruct->deployCurAntAttempted = 2;
//			}
//		}
//		//if ant2 is still available to attempt deploy
//		else if (wtc->deployStruct->deployCurAntAttempted == 2) {
//			//if ant2 HASN't been denied yet
//			if (wtc->deployStruct->deployDenyAnt2 == FALSE) {
//				//if ant2 is over the max attempts allowed
//				if (wtc->deployStruct->deployAttemptsAnt2
//						> wtc->deployStruct->deployMaxAttemptsPer) {
//					wtc->deployStruct->deployDenyAnt2 = TRUE;
//				}
//			}
//			//if ant2 HAS been denied
//			if (wtc->deployStruct->deployDenyAnt2 == TRUE) {
//				nextAntennaDetermined = FALSE;
//				// if switching antennas has already been attempted and unsuccessful
//				if (infinitLoopFlag == SET) {
//					break;
//				} else {
//					infinitLoopFlag = SET;
//				}
//				wtc->deployStruct->deployCurAntAttempted = 1;
//			}
//		}
//	}
//
//	if (nextAntennaDetermined == FALSE) {
//		//go back to main, too many attempts at deployment. Comeback Later.
//		//return status.
//		return 0;
//	}
//	return wtc->deployStruct->deployCurAntAttempted;
//}
//
//int8_t deployAntenna(UART_HandleTypeDef *huart, ADC_HandleTypeDef *hadc, RTC_HandleTypeDef *hrtc,
//		uint8_t nAntenna, uint8_t waitTime) {
//
//	RTC_DateTypeDef sdatestructureget;
//	RTC_TimeTypeDef stimestructureget;
//
//	char prompt[100] = { };
////deployAntenna
////UHF_Power_Enable
//
//	int8_t status = 0;
//	uint8_t wantedStatus;
//	if (nAntenna == 1) {
//		writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_SET);
//		wantedStatus = 1;
//	} else {
//		writeDPin(UHF_Deploy_2_GPIO_Port, UHF_Deploy_2_Pin, GPIO_PIN_SET);
//		wantedStatus = 2;
//	}
//
//	HAL_Delay(1000);
//
//	float tolerance = 0.20f;
//	uint8_t _70cm_AUX_ADC_Channel = 25;
//
//	/* Get the RTC current Time */
//	HAL_RTC_GetTime(hrtc, &stimestructureget, RTC_FORMAT_BIN);
//	/* Get the RTC current Date */
//	HAL_RTC_GetDate(hrtc, &sdatestructureget, RTC_FORMAT_BIN);
//
////example - waitTime = 10 seconds
//	uint8_t sec = (stimestructureget.Seconds + waitTime) % 60;
//	uint8_t tempS = stimestructureget.Seconds;
//	do {
//		status = deploymentSense(huart, hadc, tolerance);
//
//		/* Get the RTC current Time */
//		HAL_RTC_GetTime(hrtc, &stimestructureget, RTC_FORMAT_BIN);
//		/* Get the RTC current Date */
//		HAL_RTC_GetDate(hrtc, &sdatestructureget, RTC_FORMAT_BIN);
//		uint8_t curSec = stimestructureget.Seconds;
//		//print to UART
////		sprintf(prompt, "\t\tstatus: %d\r\n", status);
////		putS(huart, prompt);
//
//		//print to UART
//		sprintf(prompt, "deploy: %d, status: %d, reading %f V, On for %d seconds...\r",
//				(int) nAntenna, (int) (status), adcReadSingle(hadc, _70cm_AUX_ADC_Channel),
//				(int) ((60 + abs((int) (curSec - tempS))) % 60));
//		putS(huart, prompt);
//
//		HAL_Delay(200);
//
//		//timeout
//		if (sec < curSec) {
//			//status = -2;
//			break;
//		}
//	} while (status != wantedStatus && status != 3);
//
//	sprintf(prompt, "\r\n");
//	putS(huart, prompt);
//	writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_RESET);
//	writeDPin(UHF_Deploy_2_GPIO_Port, UHF_Deploy_2_Pin, GPIO_PIN_RESET);
//	HAL_Delay(100);
//	return status;
//
////UHF_Deploy_1
//
////	uint8_t thresholdV;
////	if (antenna == 1) {
////		writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_SET);
////		thresholdV = 0.6;
////	} else if (antenna == 2) {
////		writeDPin(UHF_Deploy_2_GPIO_Port, UHF_Deploy_2_Pin, GPIO_PIN_SET);
////		thresholdV = 1.7;
////	} else
////		return 0;
////
////	uint8_t dplyStatus = deploymentSense(hadc, antenna, thresholdV, dplyV);
////	writeDPin(UHF_Deploy_1_GPIO_Port, UHF_Deploy_1_Pin, GPIO_PIN_RESET);
////	//deployment sense
////	uint8_t dplySense = readDPin(_70cm_AUX_ADC_GPIO_Port, _70cm_AUX_ADC_Pin);
////
////	//UHF_Deploy_2
////
////	status = 1;
////	return status;
//}
