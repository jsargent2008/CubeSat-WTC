/*
 * stateMachine.h
 *
 *  Created on: Apr 27, 2018
 *      Author: Theodore Cox
 */

#ifndef STATEMACHINE_STATEMACHINE_H_
#define STATEMACHINE_STATEMACHINE_H_

//includes
#include <myadc/myadc.h>
#include <mygpio/mygpio.h>
#include <myrtc/myrtc.h>
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "float.h"
#include "math.h"
#include "usart.h"
#include "rtc.h"
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_adc.h"
#include "UART_IRQ/UART_IRQ.h"
#include "batteryStack.h"
#include "deployment.h"
#include "wtcStruct.h"
#include "myStructTypeDefs.h"


//function prototypes

void wtcSetup();
void commsLoop();
void groundOps();
void scienceInit();
void operations();
void stateMachine_RTC_AlarmA();

#endif /* STATEMACHINE_STATEMACHINE_H_ */
