/**
  @page TIM_InputCapture TIM example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/TIM/TIM_InputCapture/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the TIM_InputCapture example.
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

This example shows how to use the TIM peripheral to measure the frequency of
a periodic signal provided either by an external signal generator or by
another timer instance; 
Example using the STM32L1xx TIM LL API, 
peripheral initialization done using LL unitary services functions
for optimization purpose (performance and size).
  
TIM3_CH1 is configured in input capture mode. The TIM3CLK frequency is set to 
its maximum value (Prescaler is /2 * 2 = 1) in order to get the best possible resolution.
So the TIM3 counter clock is SystemCoreClock.

SystemCoreClock is set to 32 MHz for STM32L1xx Devices.

The "uwMeasuredFrequency" variable contains the measured signal frequency.
It is calculated within the capture/compare 1 interrupt service routine.

The minimum frequency value to measure is TIM3 counter clock / TIMx_CCR1 MAX
                                              = 32 MHz / 65535

Due to TIM3_IRQHandler processing time (around 3.50us), the maximum
frequency value to measure is around 300 kHz.

TIM2_CH1 is configured to generate a PWM signal.  User push-button can be used to
change the frequency of this signal from 2 kHz up to 20 kHz by steps of 2 kHz.
It is then possible to run this example without a signal generator by connecting
TIM2_CH1 to TIM3_CH1.

@par Directory contents 

  - TIM/TIM_InputCapture/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - TIM/TIM_InputCapture/Inc/main.h                  Header for main.c module
  - TIM/TIM_InputCapture/Inc/stm32_assert.h          Template file to include assert_failed function
  - TIM/TIM_InputCapture/Src/stm32l1xx_it.c          Interrupt handlers
  - TIM/TIM_InputCapture/Src/main.c                  Main program
  - TIM/TIM_InputCapture/Src/system_stm32l1xx.c      STM32L1xx system source file


@par Hardware and Software environment

  - This example runs on STM32L152xE devices.
    
  - This example has been tested with STM32L152RE-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.

  - STM32L152RE-Nucleo Rev C Set-up
    - When no signal generator is used TIM2_CH1 can be connected to TIM3_CH1:
      - TIM3_CH1  PA.6: connected to pin 13 of CN10 connector  
      - TIM2_CH1  PA.05: connected to pin 11 of CN10 connector 

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
