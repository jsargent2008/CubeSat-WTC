/**
  @page COMP_CompareGpioVsVrefInt_Window_IT COMP example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/COMP/COMP_CompareGpioVsVrefInt_Window_IT/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the COMP_CompareGpioVsVrefInt_Window_IT example.
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
This example describes how to use a pair of comparator peripherals
to compare a voltage level applied on a GPIO pin
versus 2 thresholds: the internal voltage reference (VrefInt)
and a fraction the internal voltage reference (VrefInt/2),
in interrupt mode;
This example is based on the STM32L1xx COMP LL API; 
peripheral initialization done using LL unitary services functions
for optimization purpose (performance and size).

Example configuration:
Comparator instances COMP2 and COMP1 are configured to work together
in window mode to compare 2 thresholds:
 - COMP2 input plus set to a GPIO pin (cf pin below) in analog mode.
   COMP1 input plus is not used (connected internally to the 
   same input plus as COMP2).
 - COMP2 input minus set to internal voltage reference VrefInt 
   (voltage level 1.2V, refer to device datasheet for min/typ/max values)
 - COMP1 input minus set to 1/2 of internal voltage reference VrefInt 
   (voltage level 0.6V)
Comparator interruption is enabled through EXTI lines 22 and 21
with trigger edge set to both edges rising and falling.
Comparators are set in power mode ultra low power.

Example execution:
From the main program execution, comparator is enabled.
Each time the voltage level applied on GPIO pin (comparator input plus) 
is crossing VrefInt or 1/2 VrefInt voltage thresholds (comparator input minus),
the comparator with corresponding threshold generates an interruption.
LED is turned on or off depending on the pair of comparators output state:
turned on if comparator voltage level is inside the window (between VrefInt
and 1/2 VrefInt (between 1.2V and 0.6V)), turned-off otherwise.

Connection needed:
A voltage must be supplied to the analog input pin (cf pin below),
between Vdda=3.3V and 0V. Otherwise this pin can be let floating (but in this
case COMP comparison level will be undetermined).

To check comparator window thresholds, you can:
 - Either use a wire to connect the GPIO pin of comparator input (cf pin below)
   to other connectors on board:
    - below window thresholds: to ground
    - above window thresholds: to voltage of power supply Vdda
      (on board Nucleo: Vdda=3.3V, available on CN6 pin 4 or CN7 pin 5)
    - into window thresholds: an intermediate voltage level (900mV)
      is generated for this example by DAC1 channel1, 
      connect DAC channel output to comparator input
      (see pins below, with list of GPIO used).
      This waveform generation can be disabled by commenting literal
      definition "CONSTANT_VOLTAGE_GENERATION" (in this case the pin is let floating).
 - Either use an external power supply

Other peripheral used:
  1 GPIO for LED
  1 GPIO for analog input of comparator: PB.04 (Arduino connector CN9 pin D5, Morpho connector CN10 pin 29)
  EXTI line 22 (connected to COMP2 output)
  EXTI line 21 (connected to COMP1 output)
  1 GPIO for DAC channel output PA.04 (Arduino connector CN8 pin A2, Morpho connector CN7 pin 32)

@par Directory contents 

  - COMP/COMP_CompareGpioVsVrefInt_Window_IT/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - COMP/COMP_CompareGpioVsVrefInt_Window_IT/Inc/main.h                  Header for main.c module
  - COMP/COMP_CompareGpioVsVrefInt_Window_IT/Inc/stm32_assert.h          Template file to include assert_failed function
  - COMP/COMP_CompareGpioVsVrefInt_Window_IT/Src/stm32l1xx_it.c          Interrupt handlers
  - COMP/COMP_CompareGpioVsVrefInt_Window_IT/Src/main.c                  Main program
  - COMP/COMP_CompareGpioVsVrefInt_Window_IT/Src/system_stm32l1xx.c      STM32L1xx system source file


@par Hardware and Software environment

  - This example runs on STM32L152xE devices.
    
  - This example has been tested with STM32L152RE-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.


@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
