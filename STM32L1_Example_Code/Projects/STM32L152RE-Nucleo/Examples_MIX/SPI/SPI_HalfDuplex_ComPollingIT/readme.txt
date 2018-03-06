/**
  @page SPI_HalfDuplex_ComPollingIT SPI Half Duplex IT example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    SPI/SPI_HalfDuplex_ComPollingIT/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the SPI Half Duplex IT example.
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

This example shows how to ensure SPI data buffer transmission/reception between 
two boards by using Polling (LL Driver) an interrupt mode (HAL Driver).

   _________________________                       __________________________
  |       ______ CN10 ______|                      |______ CN10 ______       |
  |      |SPI1              |                      |             SPI1 |      |
  |      |                  |                      |                  |      |
  |      |(pin 31) CLK(PB3) |______________________|(PB3)CLK  (pin 31)|      |
  |      |                  |                      |                  |      |
  |      |(pin 27) MISO(PB4)|          ____________|(PB4)MISO (pin 27)|      |
  |      |                  |          |           |                  |      |
  |      |(pin 29) MOSI(PB5)|__________|           |(PB5)MOSI (pin 29)|      |
  |      |                  |                      |                  |      |
  |      |__________________|                      |__________________|      |
  |      __                 |                      |                         |
  |     |__|                |                      |                         |
  |     USER                |                      |                         |
  |                      GND|______________________|GND                      |
  |                         |                      |                         |
  |_STM32L1 Master _________|                      |_STM32L1 Slave __________|


At the beginning of the main program the HAL_Init() function is called to reset 
all the peripherals, initialize the Flash interface and the systick.
Then the SystemClock_Config() function is used to configure the system
clock (SYSCLK) to run at 32 MHz.

The SPI peripheral configuration is ensured by the HAL_SPI_Init() function.
This later is calling the HAL_SPI_MspInit()function which core is implementing
the configuration of the needed SPI resources according to the used hardware (CLOCK & 
GPIO). You may update this function to change SPI configuration.
The Half-Duplex SPI transmission (8bit) is done using LL Driver on Master board (Tx) by using function 
LL_SPI_TransmitData8.
The The Half-Duplex SPI reception (8bit) is done using HAL Driver on Slave board (Rx) by using function 
HAL_SPI_Receive_IT.

Example execution:
First step, press the User push-button, this action initiates a Half-Duplex transfer 
between Master and Slave.
After end of transfer, aRxBuffer and aTxBuffer are compared through Buffercmp() in order to 
check buffers correctness.  

The user can choose between Master and Slave through "#define MASTER_BOARD"
in the "main.c" file.
If the Master board is used, the "#define MASTER_BOARD" must be uncommented.
If the Slave board is used the "#define MASTER_BOARD" must be commented.

STM32 board's LEDs can be used to monitor the transfer status:
 - LED2 toggles quickly on master board waiting User push-button to be pressed.
 - LED2 turns ON on slave board if reception is complete and OK.
 - LED2 toggles slowly when there is a timeout or an error in transmission/reception process.   

@note SPIx instance used and associated resources can be updated in "main.h"
      file depending hardware configuration used.

@note You need to perform a reset on Slave board, then perform it on Master board
      to have the correct behaviour of this example.

@note Care must be taken when using HAL_Delay(), this function provides accurate delay (in milliseconds)
      based on variable incremented in SysTick ISR. This implies that if HAL_Delay() is called from
      a peripheral ISR process, then the SysTick interrupt must have higher priority (numerically lower)
      than the peripheral interrupt. Otherwise the caller ISR process will be blocked.
      To change the SysTick interrupt priority you have to use HAL_NVIC_SetPriority() function.

@note The application need to ensure that the SysTick time base is always set to 1 millisecond
      to have correct HAL operation.

@par Directory contents 

  - Examples_MIX/SPI/SPI_HalfDuplex_ComPollingIT/Inc/stm32l1xx_hal_conf.h    HAL configuration file
  - Examples_MIX/SPI/SPI_HalfDuplex_ComPollingIT/Inc/stm32l1xx_it.h          SPI interrupt handlers header file
  - Examples_MIX/SPI/SPI_HalfDuplex_ComPollingIT/Inc/main.h                  Header for main.c module  
  - Examples_MIX/SPI/SPI_HalfDuplex_ComPollingIT/Src/stm32l1xx_it.c          SPI interrupt handlers
  - Examples_MIX/SPI/SPI_HalfDuplex_ComPollingIT/Src/main.c                  Main program
  - Examples_MIX/SPI/SPI_HalfDuplex_ComPollingIT/Src/system_stm32l1xx.c      STM32L1xx system source file
  - Examples_MIX/SPI/SPI_HalfDuplex_ComPollingIT/Src/stm32l1xx_hal_msp.c     HAL MSP file    


@par Hardware and Software environment

  - This example runs on STM32L152xE devices.

  - Take care to cable connection between Master and Slave Board:
    Cable shall be smaller than 5 cm and rigid if possible.

  - This example has been tested with STM32L152RE-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.

  - STM32L152RE-Nucleo Rev C Set-up
    - Connect Master board PB3 to Slave Board PB3 (Arduino D3)
    - Connect Master board PB5 (Arduino D4) to Slave Board PB4 (Arduino D5)
    - Connect Master board GND to Slave Board GND

@par How to use it ? 

In order to make the program work, you must do the following:
 - Open your preferred toolchain 
 - Rebuild all files and load your image into target memory
    o Uncomment "#define MASTER_BOARD" and load the project in Master Board
    o Comment "#define MASTER_BOARD" and load the project in Slave Board
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
 