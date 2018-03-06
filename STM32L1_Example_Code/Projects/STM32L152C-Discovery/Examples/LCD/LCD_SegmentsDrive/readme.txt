/**
  @page LCD_SegmentsDrive LCD Segments Drive example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    LCD/LCD_SegmentsDrive/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the LCD Segments Drive example.
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

This example provides a description of how to use the embedded LCD controller to drive 
the Pacific Display LCD glass mounted on board.

The goal of this example is to display a "STM32L1xx" string on LCD glass in scrolling
mode. The scrolling number is fixed to 100 repetition and the speed is fixed to 
SCROLL_SPEED_LOW ms (defined in stm32l152c_discovery_glass_lcd.h file).

@note Care must be taken when using HAL_Delay(), this function provides accurate
      delay (in milliseconds) based on variable incremented in SysTick ISR. This
      implies that if HAL_Delay() is called from a peripheral ISR process, then 
      the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.
      
@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - LCD/LCD_SegmentsDrive/Inc/stm32l1xx_hal_conf.h    HAL configuration file
  - LCD/LCD_SegmentsDrive/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - LCD/LCD_SegmentsDrive/Inc/main.h                  Header for main.c module  
  - LCD/LCD_SegmentsDrive/Src/stm32l1xx_it.c          Interrupt handlers
  - LCD/LCD_SegmentsDrive/Src/main.c                  Main program
  - LCD/LCD_SegmentsDrive/Src/stm32l1xx_hal_msp.c     HAL MSP file
  - LCD/LCD_SegmentsDrive/Src/system_stm32l1xx.c      STM32L1xx system source file


@par Hardware and Software environment

  - This example runs on STM32L152xC devices.
    
  - This example has been tested with STMicroelectronics STM32L152C-Discovery
    board and can be easily tailored to any other supported device
    and development board.      

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example


 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
