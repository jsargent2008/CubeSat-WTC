/**
  ******************************************************************************
  * @file    Examples_LL/I2C/I2C_TwoBoards_MasterRx_SlaveTx_IT/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_ll_bus.h"
#include "stm32l1xx_ll_rcc.h"
#include "stm32l1xx_ll_system.h"
#include "stm32l1xx_ll_utils.h"
#include "stm32l1xx_ll_gpio.h"
#include "stm32l1xx_ll_exti.h"
#include "stm32l1xx_ll_i2c.h"
#include "stm32l1xx_ll_pwr.h"
#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
  * @brief LED2 
  */

#define LED2_PIN                           LL_GPIO_PIN_5
#define LED2_GPIO_PORT                     GPIOA
#define LED2_GPIO_CLK_ENABLE()             LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)

/**
  * @brief Toggle periods for various blinking modes
  */

#define LED_BLINK_FAST  200
#define LED_BLINK_SLOW  500
#define LED_BLINK_ERROR 1000


/**
  * @brief Key push-button
  */
#define USER_BUTTON_PIN                         LL_GPIO_PIN_13
#define USER_BUTTON_GPIO_PORT                   GPIOC
#define USER_BUTTON_GPIO_CLK_ENABLE()           LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC)
#define USER_BUTTON_EXTI_LINE                   LL_EXTI_LINE_13
#define USER_BUTTON_EXTI_IRQn                   EXTI15_10_IRQn
#define USER_BUTTON_EXTI_LINE_ENABLE()          LL_EXTI_EnableIT_0_31(USER_BUTTON_EXTI_LINE)   
#define USER_BUTTON_EXTI_FALLING_TRIG_ENABLE()  LL_EXTI_EnableFallingTrig_0_31(USER_BUTTON_EXTI_LINE)   
#define USER_BUTTON_SYSCFG_SET_EXTI()           do {                                                                     \
                                                  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);                  \
                                                  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13);  \
                                                } while(0)
#define USER_BUTTON_IRQHANDLER                  EXTI15_10_IRQHandler

/**
  * @brief Slave settings
  */
#define SLAVE_OWN_ADDRESS                       0x5A /* This value is a left shift of a real 7 bits of a slave address
                                                        value which can find in a Datasheet as example: b0101101
                                                        mean in uint8_t equivalent at 0x2D and this value can be
                                                        seen in the OAR1 register in bits ADD[1:7] */

/**
  * @brief Master Transfer Request Direction
  */
#define I2C_REQUEST_WRITE                       0x00
#define I2C_REQUEST_READ                        0x01

/* Uncomment this line to use the board as slave, if not it is used as master */
//#define SLAVE_BOARD

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
/* IRQ Handler treatment functions */
#ifdef SLAVE_BOARD
void Slave_Ready_To_Transmit_Callback(void);
void Slave_Complete_Callback(void);
#else /* MASTER_BOARD */
void Master_Reception_Callback(void);
void Master_Complete_Callback(void);
#endif /* SLAVE_BOARD */
void UserButton_Callback(void);
void Error_Callback(void);
#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
