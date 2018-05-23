/*
 * adc.c
 *
 *  Created on: Apr 7, 2018
 *      Author: Administrator
 */

#include <myadc/myadc.h>

int ADCValue;
/**
 * @brief  ADC measurement digital
 * @param	hadc: pointer to ADC_HandleTypeDef
 * @retval val of ADC conversion
 */
float adcReadSingle(uint32_t channel) {

	ADC_ChannelConfTypeDef sConfig;
	sConfig.Channel = channel;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES;
	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}
	//HAL_ADC_Start(hadc);
	HAL_ADC_Start_IT(&hadc);
	HAL_ADC_PollForConversion(&hadc, 100);
	HAL_ADC_Stop(&hadc);
	return adcToVoltage(&hadc);
}
// adcToVoltage currently does not work
// issues with float data type
float adcToVoltage(ADC_HandleTypeDef *hadc) {
	float f = (float) HAL_ADC_GetValue(hadc);
	f /= 4095;
	f *= 3.3;
	return f;
}

//void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* AdcHandle)
//{
//	g_ADCValue = HAL_ADC_GetValue(AdcHandle);
//}
//
//void ADC_IRQHandler()
//{
//	HAL_ADC_IRQHandler(&g_AdcHandle);
//}
