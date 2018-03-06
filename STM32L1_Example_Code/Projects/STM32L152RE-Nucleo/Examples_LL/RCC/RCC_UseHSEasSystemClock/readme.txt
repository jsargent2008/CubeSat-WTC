/**
  @page RCC_UseHSEasSystemClock RCC Clock Config example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/RCC/RCC_UseHSEasSystemClock/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the RCC HSE start example.
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
This example describes how to use the RCC LL API how to start the HSE 
and use it as system clock.

At start-up, MSI clock is used as system clock (default clock after reset) and then Systick is 
configured at 1 ms after calculation of MSI frequency.

Then, HSE is started and we wait for ready state. System clock is set to HSE thanks to IT 
triggered by HSE ready.
- LED2 is turned ON to indicate that HSE is ready.
- LED2 is toggled with a timing of 1 second in case of error to switch SYSCLK to HSE or if HSE CSS
failure is detected (through NMI IT).

 @note In HSE bypass mode, input clock will come from the MCO from
       ST_LINK MCU. This frequency cannot be changed, and it is fixed
       at 8 MHz. To use MCO from ST_LINK you need to check the Board
       User Manual to know how to connect the MCO pin to the STM32 device.

@par Directory contents 

  - RCC/RCC_UseHSEasSystemClock/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - RCC/RCC_UseHSEasSystemClock/Inc/main.h                  Header for main.c module
  - RCC/RCC_UseHSEasSystemClock/Inc/stm32_assert.h          Template file to include assert_failed function
  - RCC/RCC_UseHSEasSystemClock/Src/stm32l1xx_it.c          Interrupt handlers
  - RCC/RCC_UseHSEasSystemClock/Src/main.c                  Main program
  - RCC/RCC_UseHSEasSystemClock/Src/system_stm32l1xx.c      STM32L1xx system source file

@par Hardware and Software environment

  - This example runs on STM32L152xE devices.
    
  - This example has been tested with STM32L152RE-Nucleo Rev C 
    board and can be easily tailored to any other supported device
    and development board.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
