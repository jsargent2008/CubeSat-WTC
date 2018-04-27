/*
 * stateMachine.h
 *
 *  Created on: Apr 27, 2018
 *      Author: Administrator
 */

#ifndef STATEMACHINE_STATEMACHINE_H_
#define STATEMACHINE_STATEMACHINE_H_

//includes
#include "main.h"
#include "float.h"
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_adc.h"
#include "gpio/gpio.h"
#include "adc/adc.h"

//function prototypes

void wtcSetup(ADC_HandleTypeDef *hadc);
uint8_t depolyAntenna(ADC_HandleTypeDef *hadc, uint8_t antenna);
uint8_t deploymentSense(ADC_HandleTypeDef *hadc, uint8_t antenna, uint8_t thresholdV, float dplyV);
void commsLoop();
void groundOps();
void scienceInit();
void operations();

#endif /* STATEMACHINE_STATEMACHINE_H_ */
