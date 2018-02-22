#include "LTC2991.h"

#define LTCrocks TRUE;


/**
  * @brief  Write an amount of data in blocking mode to a specific memory address
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  * @retval HAL status
  */
void SetupLTC(I2C_HandleTypeDef *hi2c, uint8_t *pData01) {
	uint8_t datatosend[2];
	datatosend[0] = 0x01;
	datatosend[1] = 0xF8;
	uint8_t data2send = 0xF8;

	HAL_Delay(100);
	//HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
	HAL_I2C_Mem_Write(hi2c, 0x90, 0x01, I2C_MEMADD_SIZE_8BIT, &data2send, 1,
			1000); //enable all channels
	return;
}

void ReadLTC(I2C_HandleTypeDef *hi2c, uint8_t *pData01)
{
	HAL_Delay(100);
    HAL_I2C_Mem_Read(hi2c, 0x90, 0x01, I2C_MEMADD_SIZE_8BIT, pData01, 1, 1000); //status of channels
    //HAL_StatusTypeDef HAL_I2C_IsDeviceReady(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint32_t Trials, uint32_t Timeout);
    	  //HAL_I2C_IsDeviceReady(&hi2c2,0x90, 1, 100);

    	  /* HAL_StatusTypeDef HAL_I2C_Mem_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
    	   *
    		HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout);
    	   	 HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
    	   	 */

    	  //HAL_I2C_Mem_Read(&hi2c2, 0x90, 0x01, I2C_MEMADD_SIZE_8BIT, &pData01, 1, 1000); //status of channels

    	  //I2CError = HAL_I2C_Mem_Write(&hi2c2, 0x90, *datatosend, I2C_MEMADD_SIZE_8BIT, &pData01, 1, 1000); //enable all channels
    	  //HAL_Delay(100);
    	  //HAL_I2C_Mem_Read(&hi2c2, 0x90, 0x00, I2C_MEMADD_SIZE_8BIT, &pData01, 1, 1000); //status of channels
    	  /*HAL_Delay(100);
    	  HAL_Delay(100);
    	  HAL_I2C_Mem_Read(&hi2c2, 0x90, 0x01, I2C_MEMADD_SIZE_8BIT, &pData01, 1, 1000); //status of channels
    	  HAL_Delay(100);
    	  HAL_I2C_Mem_Write(&hi2c2, 0x90, 0xF0, I2C_MEMADD_SIZE_8BIT, &pData01, 1, 1000); //enable all channels*/

    	  //HAL_Delay(1000);
    	  //pData06 = 0x06;
    	   //HAL_I2C_Master_Transmit(&hi2c2, 0x90, &pData06, 1, 10000);
    	  //I2CError =
    	   //printf("%i\n",I2CError);
    	  //HAL_Delay(1000);
    	  //HAL_I2C_Mem_Read(&hi2c2,0x90, 0x07, I2C_MEMADD_SIZE_8BIT, &pData07, 1, 1000);
    	  //HAL_Delay(1000);
    	  //HAL_I2C_Mem_Read(&hi2c2,0x90, 0x08, I2C_MEMADD_SIZE_8BIT, &pData08, 1, 1000);
    	  //HAL_Delay(50);
    return;
}
