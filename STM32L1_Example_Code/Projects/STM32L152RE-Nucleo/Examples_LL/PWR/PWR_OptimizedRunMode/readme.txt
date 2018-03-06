/**
  @page PWR_OptimizedRunMode PWR standby example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/PWR/PWR_OptimizedRunMode/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the PWR Optimized Run Mode example.
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

This example shows how to increase/decrease Frequency and Vcore and how to enter/exit
LowPowerRun Mode.

In the associated software, the system clock is set to 32 MHz, an EXTI line
is connected to the User push-button through PC.13 and configured to generate an 
interrupt on falling edge upon key press.

After start-up LED2 is toggling FAST(100-ms blinking period), indicates that device 
is running at 32MHz.

LED toggling speed is controlled by variable "uhLedBlinkSpeed".

The User push-button can be pressed at any time to change Frequency, VCore(VOS) 
and Low Power Run mode. 

Initial STATE: 
--> Freq: 32MHz, VCore 1.8V, Core in Run Mode
--> LED2 toggling FAST (100ms)   - wait User push-button action

STATE 2: 
User push-button pressed:
--> Freq: 4MHz, VCore 1.2V, Core in Run Mode
--> LED2 toggling MEDIUM (200ms) - wait User push-button action

STATE 3: 
User push-button pressed:
--> Freq:  131KHz, VCore 1.2V, Core in Low Power Run Mode
--> LED2 toggling SLOW (400ms)   - wait User push-button action

STATE 4: 
User push-button pressed:
--> Freq: 4MHz, VCore 1.2V, Core in Run Mode
--> LED2 toggling MEDIUM (200ms) - wait User push-button action

Final STATE: 
User push-button pressed:
--> Freq: 32MHz, VCore 1.8V, Core in Run Mode
--> LED2 toggling FAST (100ms) in infinite loop


@note To measure the current consumption in Run mode, remove JP6 jumper 
      and connect an ampere meter to JP6 to measure IDD current.
      NB: LED2 have an impact on power consumption. 
          Remove LED2 blinking to have a stable power consumption, 
          comment line  "#define USE_LED" in main.c file  
@par Directory contents 

  - PWR/PWR_OptimizedRunMode/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - PWR/PWR_OptimizedRunMode/Inc/main.h                  Header for main.c module
  - PWR/PWR_OptimizedRunMode/Inc/stm32_assert.h          Template file to include assert_failed function
  - PWR/PWR_OptimizedRunMode/Src/stm32l1xx_it.c          Interrupt handlers
  - PWR/PWR_OptimizedRunMode/Src/main.c                  Main program
  - PWR/PWR_OptimizedRunMode/Src/system_stm32l1xx.c      STM32L1xx system source file


@par Hardware and Software environment

  - This example runs on STM32L152xE devices.
    
  - This example has been tested with STMicroelectronics STM32L152RE-Nucleo Rev C
    board and can be easily tailored to any other supported device
    and development board.

  - STM32L152RE-Nucleo Rev C Set-up
    - LED2 connected to PA.05 pin
    - User push-button connected to pin PC.13 (External line 15 to 10)

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
