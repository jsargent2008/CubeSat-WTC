/*
 * adc.h
 *
 *  Created on: Apr 7, 2018
 *      Author: Administrator
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_

#include "main.h"
#include "float.h"
#include "stm32l1xx_hal.h"
#include "stm32l1xx_hal_adc.h"


/* Private define ------------------------------------------------------------*/
#define VDD_THEORY                    ((uint32_t)3300)    /* Value of analog voltage supply Vdda (unit: mV) */
#define RANGE_12BITS                   ((uint32_t)4095)    /* Max value with a full range of 12 bits */
/* Private macro -------------------------------------------------------------*/
/**
 * @brief  Computation of voltage (unit: mV) from ADC measurement digital
 *         value on range 12 bits.
 *         Calculation validity conditioned to settings:
 *          - ADC resolution 12 bits (need to scale value if using a different
 *            resolution).
 *          - Power supply of analog voltage Vdda 3.3V (need to scale value
 *            if using a different analog voltage supply value).
 * @param ADC_DATA: Digital value measured by ADC
 * @retval None
 */
#define ADC_BITS_TO_VOLTAGE(ADC_DATA)                        \
  ( (ADC_DATA) * VDD_THEORY / RANGE_12BITS)


float adcReadSingle(ADC_HandleTypeDef *hadc, uint32_t channel);
/**
 * @brief  ADC measurement digital
 * @param	hadc: pointer to ADC_HandleTypeDef
 * @retval val of ADC conversion
 */
float adcToVoltage(ADC_HandleTypeDef *hadc);

#endif /* ADC_ADC_H_ */
