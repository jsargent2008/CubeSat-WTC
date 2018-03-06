/**
  @page PWR_STOP_RTC Power Stop Mode Example 
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    PWR/PWR_STOP_RTC/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the Power Stop Mode using RTC example.
  ******************************************************************************
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
  @endverbatim

@par Example Description 

This example shows how to enter Stop mode and wake up from this mode by using the RTC 
wakeup timer event connected to an interrupt.

This example shows also how to configure the STM32L1xx system to measure 
STOP mode with RTC current consumption.

In the associated software, the system clock is set to 32 MHz, the SysTick is 
programmed to generate an interrupt each 1 ms.
The Low Speed Internal (LSI) clock is used as RTC clock source by default.

In the associated software
  - the system clock is set to 32 MHz.
  - the EXTI_Line20 connected internally to the RTC Wakeup event is configured
    to generate an interrupt on rising edge each 4s.
  - the SysTick is programmed to generate an interrupt each 1 ms. 

The system enters STOP mode after 5s and will wait for the RTC Wakeup event to be
generated each 4s. Current consumption could be monitored through an amperemeter.
After the system woken up from STOP, the clock system should be reconfigured to HSI 
because the default clock after wake up is the MSI.

The above scenario is repeated in an infinite loop.
 - LED2 ON: HAL configuration failed (system will go to an infinite loop)
 
    - STOP Mode with RTC clocked by LSI
    ===================================  
            - RTC Clocked by LSI
            - Regulator in LP mode
            - VREFINT OFF with fast wakeup enabled
            - MSI as SysClk after Wake Up
            - No IWDG
            - Automatic Wakeup using RTC on LSI (after ~4s)


@note This example can not be used in DEBUG mode, this is due to the fact 
      that the Cortex-M3 core is no longer clocked during low power mode 
       so debugging features are disabled

@note Care must be taken when HAL_RCCEx_PeriphCLKConfig() is used to select 
      the RTC clock source; in this case the Backup domain will be reset in  
      order to modify the RTC Clock source, as consequence RTC registers (including 
      the backup registers) and RCC_CSR register are set to their reset values.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.
      
@par Directory contents 

  - PWR/PWR_STOP_RTC/Inc/stm32l1xx_conf.h         HAL Configuration file
  - PWR/PWR_STOP_RTC/Inc/stm32l1xx_it.h           Header for stm32l1xx_it.c
  - PWR/PWR_STOP_RTC/Inc/main.h                   Header file for main.c
  - PWR/PWR_STOP_RTC/Src/system_stm32l1xx.c       STM32L1xx system clock configuration file
  - PWR/PWR_STOP_RTC/Src/stm32l1xx_it.c           Interrupt handlers
  - PWR/PWR_STOP_RTC/Src/main.c                   Main program
  - PWR/PWR_STOP_RTC/Src/stm32l1xx_hal_msp.c  HAL MSP module

@par Hardware and Software environment

  - This example runs on STM32L152xE devices
    
      
  - This example has been tested with STMicroelectronics STM32L152RE-Nucleo Rev C
    board and can be easily tailored to any other supported device 
    and development board.

  - STM32L152RE-Nucleo Rev C Set-up
    - Connect an amperemeter to JP6 to measure the IDD current

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
