/*
 * memoryMap.h
 *
 *  Created on: Apr 25, 2018
 *      Author: Administrator
 */

#ifndef MEMORYMAP_MEMORYMAP_H_
#define MEMORYMAP_MEMORYMAP_H_


// includes

#include "gpio/gpio.h"

/* Private define ------------------------------------------------------------*/

// 	READ IMPORTANT REMINDER!!!
//	increment each 32-bit variable memory address by 0x10
//	increment each 16-bit variable memory address by 0x01
//	increment each 08-bit variable memory address by 0b00001000
//	^^^ better to group 08-values into pairs of 2 (16-bit) or 4 (32-bit)

// used with RTC library
#define sysMem_lastChk_RTC_Time   	((uint32_t)0x08080000) /* Base @ of Page 0, 256 bytes */
#define sysMem_lastChk_RTC_Date  	((uint32_t)0x08080010) /* Base @ of Page 1, 256 bytes */


//status of every digital IO coming out of the STM32
// note: labels were taken directly from the KiCad schematic for the WTC R2.
// QPACE

#define sysMem_5V_Rail_1_Enable		((uint32_t)0x08080200) /* Base @ of Page 2, 256 bytes */
#define sysMem_70cm_AUX_GPIO   		((uint32_t)0x08080300) /* Base @ of Page 3, 256 bytes */

//------------COPY TEXT BELOW------------

#define sysMem_70cm_Primary_Enable_p79		((uint32_t)0x80080000)
#define sysMem_EN_MPPT_YZ_p97				((uint32_t)0x80080001)
#define sysMem_Pwr_En_Pi1_p57				((uint32_t)0x80080002)
#define sysMem_RF_Deck_Power_Enable_p37		((uint32_t)0x80080003)
#define sysMem_12V_1_Enable_p64				((uint32_t)0x80080004)
#define sysMem_Pgood_332_p83				((uint32_t)0x80080005)
#define sysMem_12V_2_Enable_p65				((uint32_t)0x80080006)
#define sysMem_EN_MPPT_Z_p85				((uint32_t)0x80080007)
#define sysMem_EN_MPPT_YZ_p86				((uint32_t)0x80080008)
#define sysMem_JTG1_p88						((uint32_t)0x80080009)
#define sysMem_Pgood_331_p82				((uint32_t)0x8008000a)
#define sysMem_Kill_Switch_2_p45			((uint32_t)0x8008000b)
#define sysMem_Kill_Switch_1_p44			((uint32_t)0x8008000c)
#define sysMem_70cm_Secondary_Enable_p80	((uint32_t)0x8008000d)
#define sysMem_Battery_Reset_2_p3			((uint32_t)0x8008000e)
#define sysMem_WTC_EN_Chrg_p1				((uint32_t)0x8008000f)
#define sysMem_Battery_Reset_1_p2			((uint32_t)0x80080010)
#define sysMem_5V_Rail_1_Enable_p70			((uint32_t)0x80080011)
#define sysMem_WTC_BUS_Switch_Pi_Select_p59	((uint32_t)0x80080012)
#define sysMem_Pi_Heartbeat_Pi1_p61			((uint32_t)0x80080013)
#define sysMem_Pwr_En_Pi2_p58				((uint32_t)0x80080014)
#define sysMem_Pi_Heartbeat_Pi2_p60			((uint32_t)0x80080015)
#define sysMem_5V_Rail_2_Enable_p72			((uint32_t)0x80080016)
#define sysMem_EN_NTC_Drive_p92				((uint32_t)0x80080017)
#define sysMem_EN_MPPT_XZ_p89				((uint32_t)0x80080018)
#define sysMem_EN_MPPT_YCtr_p87				((uint32_t)0x80080019)
#define sysMem_EN_MPPT_XZ_p91				((uint32_t)0x8008001a)
#define sysMem_EN_MPPT_XCtr_p90				((uint32_t)0x8008001b)
#define sysMem_Deployment_Power_Enable_p94	((uint32_t)0x8008001c)
#define sysMem_UHF_Power_Enable_p95			((uint32_t)0x8008001d)

//------------COPY TEXT ABOVE------------
uint8_t gpioAllDump();
uint8_t gpioPortDump(char port);
uint32_t gpioStatusRetrieve(char port);
#endif /* MEMORYMAP_MEMORYMAP_H_ */
