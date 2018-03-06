/**
  @page ADC_TemperatureSensor ADC example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/ADC/ADC_TemperatureSensor/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the ADC_TemperatureSensor example.
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
This example describes how to use a ADC peripheral to perform 
a single ADC conversion of the internal temperature sensor 
and to calculate the temperature in Celsius degrees; 
Example using programming model: polling 
(for programming models interrupt or DMA transfer, refer to
other examples); 
This example is based on the STM32L1xx ADC LL API; 
peripheral initialization done using LL unitary services functions
for optimization purpose (performance and size).

Example configuration:
ADC is configured to convert a single channel, in single conversion mode,
from SW trigger.
Sequencer of group regular (default group available on ADC of all STM32 devices)
is configured to convert 1 channel: internal channel temperature sensor.

Example execution:
At each press on push button, the ADC performs 1 conversion of the selected channel.
Software polls for conversion completion.
When conversion is completed, main program reads conversion data
from ADC data register and stores it into a variable, LED is turned on.

ADC conversions raw data are computed to physical values
using LL ADC driver helper macro:
 - Value of temperature (unit: degree Celcius)

For debug: variables to monitor with debugger watch window:
 - "uhADCxConvertedData": ADC group regular conversion data
 - "hADCxConvertedData_Temperature_DegreeCelsius": Value of temperature (unit: degree Celcius)

Connection needed:
None.

Other peripherals used:
  1 GPIO for push button
  1 GPIO for LED

@par Directory contents 

  - ADC/ADC_TemperatureSensor/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - ADC/ADC_TemperatureSensor/Inc/main.h                  Header for main.c module
  - ADC/ADC_TemperatureSensor/Inc/stm32_assert.h          Template file to include assert_failed function
  - ADC/ADC_TemperatureSensor/Src/stm32l1xx_it.c          Interrupt handlers
  - ADC/ADC_TemperatureSensor/Src/main.c                  Main program
  - ADC/ADC_TemperatureSensor/Src/system_stm32l1xx.c      STM32L1xx system source file


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
