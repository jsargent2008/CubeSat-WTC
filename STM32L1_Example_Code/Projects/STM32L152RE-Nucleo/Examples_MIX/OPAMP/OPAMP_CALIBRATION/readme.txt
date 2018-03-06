/**
  @page OPAMP_CALIBRATION OPAMP example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_MIX/OPAMP/OPAMP_CALIBRATION/readme.txt
  * @author  MCD Application Team
  * @brief   Description of the OPAMP_CALIBRATION example.
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
peripheral with OPAMP calibration and operation; 
This example is based on the STM32L1xx OPAMP HAL & LL API
(LL API used for performance improvement).

Example configuration:
Operational amplifier instance OPAMP2 is configured in follower mode.
OPAMP non-inverting input and output are set to be connected to GPIO pins.
OPAMP inverting input is not connected externally (internal connection in follower mode).

Other peripherals configured in this example:
One DAC channel, one DMA channel and one timer are configured to generate a voltage
waveform to test the OPAMP: sinus waveform.


Example execution:
OPAMP calibration done using HAL driver, because requires to follow a particular
procedure. HAL OPAMP driver provides this service.
Then, switch from HAL driver to LL driver (caution: any further switch back to
HAL driver is not possible).
Following OPAMP operations are done using LL driver because actions are
more light and quick: OPAMP enable, OPAMP settings update.


This example shows how to:
- Get factory calibration (trimming) settings.
- Enable/disable OPAMP
- Calibrate OPAMP peripheral before use of OPAMP.
  Hence changes can be monitored (versus factory settings or in case of 
  temperature impact for instance).

Push the Key Push button (connected to PC.13 pin) to switch from one step to the 
next one.
Key push button steps are:
  -> 1st Push: 
     + Factory trimming retrieved 
     + User trimming set according to self calibration (1st run)
     + Factory trimming and user trimming are compared
       - If The LED blinks rapidly: Calibrated trimming are different from Factory Trimming
       - ................. slowly : Calibrated trimming same as Factory Trimming 
  -> 2nd Push:
     + OPAMP start
     + Use of previously calibrated user Trimming values
  -> 3rd Push:
     + change OPAMP setting on the fly (dummy change, without application purpose in this example: change non-inverting input source)
  -> 4th Push:
     + OPAMP stopped
  -> 5th Push: end of test


Connection needed:
To check OPAMP amplification, you can either:
 - Use the waveform generated in this example by DAC channel:
   connect DAC channel output PA.04 to OPAMP non-inverting input PA.06.
 - Connect a voltage to OPAMP non-inverting input PA.06
   between ground (0V) and Vdda (3.3V).
Voltage amplified by the OPAMP can be observed on OPAMP output (see pins below, with list of GPIO used).

Other peripheral used:
  1 GPIO for push button
  1 GPIO for DAC channel output PA.04 (Arduino connector CN8 pin A2, Morpho connector CN7 pin 32)
  1 GPIO for OPAMP non-inverting input: PA.06 (Arduino connector CN5 pin D12, Morpho connector CN10 pin 13)
  1 GPIO for OPAMP output: PB.00 (Arduino connector CN8 pin A3, Morpho connector CN7 pin 34)
  For waveform generation: 1 DAC channel, 1 DMA channel, 1 timer.

@par Directory contents 

  - OPAMP/OPAMP_CALIBRATION/Inc/stm32l1xx_hal_conf.h    HAL configuration file
  - OPAMP/OPAMP_CALIBRATION/Inc/stm32l1xx_it.h          DMA interrupt handlers header file
  - OPAMP/OPAMP_CALIBRATION/Inc/main.h                        Header for main.c module  
  - OPAMP/OPAMP_CALIBRATION/Src/stm32l1xx_it.c          DMA interrupt handlers
  - OPAMP/OPAMP_CALIBRATION/Src/main.c                        Main program
  - OPAMP/OPAMP_CALIBRATION/Src/stm32l1xx_hal_msp.c     HAL MSP file
  - OPAMP/OPAMP_CALIBRATION/Src/system_stm32l1xx.c      STM32L1xx system source file

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
