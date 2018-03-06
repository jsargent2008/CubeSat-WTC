/**
  @page OPAMP_Follower OPAMP example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/OPAMP/OPAMP_Follower/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the OPAMP_Follower example.
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
This example describes how to use a operational amplifier
peripheral in follower mode; 
To test OPAMP in this example, a voltage waveform is generated 
by DAC peripheral and can be connected to OPAMP input; 
This example is based on the STM32L1xx OPAMP LL API; 
peripheral initialization done using LL unitary services functions
for optimization purpose (performance and size).

Example configuration:
Operational amplifier instance OPAMP2 is configured in PGA mode.
OPAMP non-inverting input and output are set to be connected to GPIO pins.
OPAMP inverting input is not connected externally (internal connection in PGA mode).

Other peripherals configured in this example:
One DAC channel, one DMA channel and one timer are configured to generate a voltage
waveform to test the OPAMP:
sinus waveform, frequency 1kHz, amplitude Vdda.

Example execution:
From the main program execution, LED is toggling quickly while waiting for
user button press.
Then, the OPAMP is enabled and the waveform to test OPAMP is generated.

Connection needed:
To check OPAMP functionality, you can:
 - Either use the waveform generated in this example by DAC1 channel1:
   connect DAC channel output to OPAMP non-inverting input (see pins below, with list of GPIO used).
   This waveform generation can be disabled by commenting literal definition "WAVEFORM_VOLTAGE_GENERATION".
 - Either connect a voltage to OPAMP non-inverting input (see pins below, with list of GPIO used)
   between ground (0V) and Vdda (3.3V).
 - Either use an external power supply
Voltage amplified by the OPAMP can be observed on OPAMP output (see pins below, with list of GPIO used).

Other peripheral used:
  1 GPIO for push button
  1 GPIO for DAC channel output PA.04 (Arduino connector CN8 pin A2, Morpho connector CN7 pin 32)
  1 GPIO for OPAMP non-inverting input: PA.06 (Arduino connector CN5 pin D12, Morpho connector CN10 pin 13)
  1 GPIO for OPAMP output: PB.00 (Arduino connector CN8 pin A3, Morpho connector CN7 pin 34)
  For waveform voltage generation: 1 DAC channel, 1 DMA channel, 1 timer.


@par Directory contents 

  - OPAMP/OPAMP_Follower/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - OPAMP/OPAMP_Follower/Inc/main.h                  Header for main.c module
  - OPAMP/OPAMP_Follower/Inc/stm32_assert.h          Template file to include assert_failed function
  - OPAMP/OPAMP_Follower/Src/stm32l1xx_it.c          Interrupt handlers
  - OPAMP/OPAMP_Follower/Src/main.c                  Main program
  - OPAMP/OPAMP_Follower/Src/system_stm32l1xx.c      STM32L1xx system source file


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
