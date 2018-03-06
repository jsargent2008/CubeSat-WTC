/**
  @page OPAMP_InternalFollower OPAMP used as internal follower
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    OPAMP/OPAMP_InternalFollower/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the OPAMP internal follower example.
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

This example provides a short description of how to configure the OPAMP in internal 
follower mode (unity gain). The signal applied on OPAMP non-inverting input is 
reproduced on OPAMP output.

Other peripherals are used in this example:
 - DAC generates continuously a signal on OPAMP2 non-inverting input (internal connection: no external connection needed)
   This signal can be observed on pin PA.04 (output of DAC_CHANNEL_1 has been connected to this GPIO pin for debug)

   Note: External connection between DAC output and OPAMP non-inverting input is possible:
         Change OPAMP init parameter "NonInvertingInput" from "OPAMP_NONINVERTINGINPUT_DAC_CH1" to "OPAMP_NONINVERTINGINPUT_IO0",
         then connect a wire between pin PA.04 (output of DAC_CHANNEL_1) and pin PA.06 (non-inverting input of OPAMP).

 - ADC acquires the signal on OPAMP2 output (internal connection: no external connection needed)
   This signal can be observed on pin PB.00
   
   Note: ADC conversion results are stored into array "aADCxConvertedValues" (for debug: check into watch window)            */
         These results can be compared to reference waveform "Waveform_Ramp_12bits_5samples".                                       */

 - DAC and ADC are clock by the same timer TIMx: DAC on TIMx rising edge, ADC on TIMx falling edge
  (in order to have for each sample of DAC waveform a stabilization time of 1/2 TIMx clock cycle, then ADC acquisition of this sample).


To run the example:
 - There is no external connection needed to run this example
 - Optionally, for this example purpose: pressing on User push-button enable/disable OPAMP
   to watch the impact on OPAMP output voltage and LED status.

STM32L152RE-Nucleo Rev C board's LED is be used to monitor the program execution status:
 - Normal operation: LED2 is turned-on/off in function of OPAMP output vs input voltage
   comparison status:
    - Turn-off if OPAMP output is different of non-inverting input
    - Turn-on if OPAMP output is equal to non-inverting input
 - Error: In case of error, LED2 is toggling at a frequency of 1Hz.


@par Directory contents 

  - OPAMP/OPAMP_InternalFollower/Inc/stm32l1xx_hal_conf.h    HAL configuration file
  - OPAMP/OPAMP_InternalFollower/Inc/stm32l1xx_it.h          DMA interrupt handlers header file
  - OPAMP/OPAMP_InternalFollower/Inc/main.h                        Header for main.c module  
  - OPAMP/OPAMP_InternalFollower/Src/stm32l1xx_it.c          DMA interrupt handlers
  - OPAMP/OPAMP_InternalFollower/Src/main.c                        Main program
  - OPAMP/OPAMP_InternalFollower/Src/stm32l1xx_hal_msp.c     HAL MSP file
  - OPAMP/OPAMP_InternalFollower/Src/system_stm32l1xx.c      STM32L1xx system source file

@par Hardware and Software environment 

  - This example runs on STM32L1xx Cat.3, Cat.4, Cat.5 devices.

  - This example has been tested with STM32L152RE-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board. 

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
