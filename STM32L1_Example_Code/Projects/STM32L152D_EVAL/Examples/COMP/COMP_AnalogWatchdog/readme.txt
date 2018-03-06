/**
  @page COMP_AnalogWatchdog COMP Analog Watchdog Example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    COMP/COMP_AnalogWatchdog/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the COMP Analog Watchdog Example.
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

This example shows how to make an analog watchdog using the COMP peripherals in window mode.

  - The upper threshold is set to VREFINT = 1.22V
  - The lower threshold is set to VREFINT / 4 = 1.22V / 4 = 0.305V
  - The input voltage is configured to be connected to pin PB.05
  
LEDs on STM32L152D-EVAL can be used to monitor the voltage level compared to comparators thresholds:

- LED3 and LED1 are turned On, MCU wakes-up from STOP mode, if the input voltage is above the higher threshold.
- LED2 and LED4 are turned On, MCU wakes-up from STOP mode, if the input voltage is under the lower threshold.
- If the input voltage is within the thresholds, the MCU is set in in STOP mode (LED2 and LED4 are turned Off).


@note Care must be taken when using HAL_Delay(), this function provides 
      accurate delay (in milliseconds) based on variable incremented in SysTick ISR. 
      This implies that if HAL_Delay() is called from a peripheral ISR process, then 
      the SysTick interrupt must have higher priority (numerically lower) than the 
      peripheral interrupt. Otherwise the caller ISR process will be blocked. 
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set 
      to 1 millisecond to have correct HAL operation.

@par Directory contents 

  - COMP/COMP_AnalogWatchdog/Inc/stm32l1xx_hal_conf.h    HAL configuration file
  - COMP/COMP_AnalogWatchdog/Inc/stm32l1xx_it.h          COMP interrupt handlers header file
  - COMP/COMP_AnalogWatchdog/Inc/main.h                  Header for main.c module
  - COMP/COMP_AnalogWatchdog/Src/stm32l1xx_it.c          COMP interrupt handlers
  - COMP/COMP_AnalogWatchdog/Src/main.c                  Main program
  - COMP/COMP_AnalogWatchdog/Src/stm32l1xx_hal_msp.c     HAL MSP file 
  - COMP/COMP_AnalogWatchdog/Src/system_stm32l1xx.c      STM32L1xx system source file


@par Hardware and Software environment 

  - This example runs on STM32L1xx devices.

  - This example has been tested with STM32L152D-EVAL board and can be
    easily tailored to any other supported device and development board.

  - STM32L152D-EVAL Set-up
    - Use LED1, LED2, LED3 and LED4 connected respectively to PD.03, PD.07 ,PG.14
      and PG.15 pins
      @note This example run in stand alone mode.
    - Use a wire to connect Potentiometer RV3 (pin PF.10)
      to COMP2 non inverting input (pin PB.05).
      Note: On STM32L152D-EVAL: Pin PB.05 is accessible on JP13, connector marked "COM_IN+".
      Alternatively use an external power supply and adjust supply voltage (above, within and below thresholds).
@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */