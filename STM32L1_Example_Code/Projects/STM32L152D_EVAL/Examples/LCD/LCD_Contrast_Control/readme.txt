/**
  @page LCD_Contrast_Control LCD Contrast Control example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    LCD/LCD_Contrast_Control/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the LCD Contrast Control example.
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

This example provides a description of how to use the embedded LCD GLASS  controller 
and how to Configures the LCD Contrast. 

The ADC1 is configured to converts continuously ADC channel31 when using the 
STM32L152D-EVAL. 

Each time, an end of conversion occurs, LCD GLASS contrast is updated.
The messages displayed on the Pacific Display LCD glass (XHO5002B) mounted on 
STM32L152D-EVAL board is proportional to each LCD Contrast level.

@note Care must be taken when using HAL_Delay(), this function provides accurate
      delay (in milliseconds) based on variable incremented in SysTick ISR. This
      implies that if HAL_Delay() is called from a peripheral ISR process, then 
      the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - LCD/LCD_Contrast_Control/Inc/stm32l1xx_hal_conf.h    HAL configuration file
  - LCD/LCD_Contrast_Control/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - LCD/LCD_Contrast_Control/Inc/main.h                  Header for main.c module  
  - LCD/LCD_Contrast_Control/Src/stm32l1xx_it.c          Interrupt handlers
  - LCD/LCD_Contrast_Control/Src/main.c                  Main program
  - LCD/LCD_Contrast_Control/Src/stm32l1xx_hal_msp.c     HAL MSP file
  - LCD/LCD_Contrast_Control/Src/system_stm32l1xx.c      STM32L1xx system source file


@par Hardware and Software environment

  - This example runs on STM32L1x2xx devices.
    
  - This example has been tested with STMicroelectronics STM32L152D-EVAL
    board and can be easily tailored to any other supported device
    and development board.   

  - STM32L152D-EVAL Set-up
    - Connect a variable power supply 0-3.3V to ADC Channel31 mapped on pin PF.10
      (potentiometer RV3).
    @note Make sure that the embedded LCD GLASS is in LCD position.
    @note Make sure that
        Jumper 6 (JP6) is in position 2<-->3 (SEG1).
        Jumper 8 (JP8) is in position 2<-->3 (SEG0).

  - JP7  jumper should be in position 1-2.
  - JP12 jumper should be closed.
  - JP13 jumper should be fitted in ADC position.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
