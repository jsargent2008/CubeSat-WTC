/**
  @page USART_SyncCommunication_FullDuplex_DMA USART Synchronous Transmitter/Receiver example (DMA mode)
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/USART/USART_SyncCommunication_FullDuplex_DMA/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the USART_SyncCommunication_FullDuplex_DMA example.
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

This example shows how to configure GPIO, USART, DMA and SPI peripherals 
for transmitting bytes from/to an USART peripheral to/from an SPI peripheral (in slave mode)
by using DMA mode through the STM32L1xx USART LL API. Peripheral initialization
done using LL unitary services functions for optimization purpose (performance and size).

This example works with only one STM32L152RE-Nucleo Rev C.

USART1 Peripheral is acts as Master.
SPI1 Peripheral is configured in Slave mode.
GPIO associated to User push-button is linked with EXTI. 

Example execution:

LED2 is blinking Fast (200ms) and wait User push-button action.
Press User push-button on BOARD start a Full-Duplex communication through DMA.
On USART1 side, Clock will be generated on SCK line, Transmission done on TX, reception on RX.
On SPI1 side, reception is done through the MOSI Line, transmission on MISO line.

At end of transmission, both received buffers are compared to expected ones.
In case of both transfers successfully completed, LED2 is turned on.
In case of errors, LED2 is blinking Slowly (1s).

@par Directory contents 

  - USART/USART_SyncCommunication_FullDuplex_DMA/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - USART/USART_SyncCommunication_FullDuplex_DMA/Inc/main.h                  Header for main.c module
  - USART/USART_SyncCommunication_FullDuplex_DMA/Inc/stm32_assert.h          Template file to include assert_failed function
  - USART/USART_SyncCommunication_FullDuplex_DMA/Src/stm32l1xx_it.c          Interrupt handlers
  - USART/USART_SyncCommunication_FullDuplex_DMA/Src/main.c                  Main program
  - USART/USART_SyncCommunication_FullDuplex_DMA/Src/system_stm32l1xx.c      STM32L1xx system source file

@par Hardware and Software environment

  - This example runs on STM32L152RE devices.

  - This example has been tested with STM32L152RE-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.

  - STM32L152RE-Nucleo Rev C Set-up
    - Connect USART1 SCK PA.08 to Slave SPI1 SCK PB.03
    - Connect USART1 TX PA.09 to Slave SPI1 MOSI PB.05
    - Connect USART1 RX PA.10 to Slave SPI1 MISO PB.04

Board connector:
  PA.08 :   connected to pin 23 of CN10 connector
  PA.09 :   connected to pin 21 of CN10 connector
  PA.10 :   connected to pin 33 of CN10 connector
  PB.03 :   connected to pin 31 of CN10 connector
  PB.05 :   connected to pin 29 of CN10 connector
  PB.04 :   connected to pin 27 of CN10 connector

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example
 - Launch the program. Press on User push button on board to initiate data transfers.

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
