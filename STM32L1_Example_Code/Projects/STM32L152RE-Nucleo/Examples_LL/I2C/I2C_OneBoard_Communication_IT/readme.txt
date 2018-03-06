/**
  @page I2C_OneBoard_Communication_IT I2C example (IT Mode)
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    Examples_LL/I2C/I2C_OneBoard_Communication_IT/readme.txt 
  * @author  MCD Application Team
  * @brief   Description of the I2C_OneBoard_Communication_IT I2C example (IT Mode).
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

This example describes how to receive data byte from an I2C Slave device
using IT mode to an I2C Master device using IT mode. Peripheral initialization done
using LL unitary services functions for optimization purpose (performance and size).

This example guides you through the different configuration steps by mean of LL API
to configure GPIO and I2C peripherals using only one STM32L152RE-Nucleo Rev C.

I2C1 Peripheral is configured in Slave mode with EXTI (Clock 400Khz, Own address 7-bit enabled).
I2C2 Peripheral is configured in Master mode with EXTI (Clock 400Khz).
GPIO associated to User push-button is linked with EXTI. 

LED2 blinks quickly to wait for user-button press. 

Example execution:
Press the User push-button to initiate a Start condition by Master.
This action will generate an I2C start condition on the I2C bus.
When the I2C start condition is sent on I2C2, a SB interrupt occurs.
I2C2 IRQ Handler routine is then sending the Slave address with a read bit condition.
When address Slave match code is received on I2C1, the Slave acknowledge the address.
When this acknowledge is received on I2C2, an ADDR interrupt occurs.
I2C2 IRQ Handler routine is then preparing the enable of data acknowledge and interrupts for next statement.

When address Slave match code is received on I2C1, an ADDR interrupt occurs.
I2C1 IRQ Handler routine is then checking the slave direction at Write (mean read direction for Master).
This will allow Slave to enter in transmitter mode and then send a byte when TXE interrupt occurs.
When byte is received on I2C2, an RXNE interrupt occurs.
When DR register is read, Master disable all I2C2 interrupts and generate a Non-acknowledge then a STOP condition
to inform the Slave that the transfer is finished.
The Non-acknowledge condition generate a AF interrupt in Slave side treated in the I2C1 IRQ handler routine by a clear of NACK flag
and disable all I2C1 interrupts.

LED2 is On if data is well received.

In case of errors, LED2 is blinking.

@par Directory contents 

  - I2C/I2C_OneBoard_Communication_IT/Inc/stm32l1xx_it.h          Interrupt handlers header file
  - I2C/I2C_OneBoard_Communication_IT/Inc/main.h                  Header for main.c module
  - I2C/I2C_OneBoard_Communication_IT/Inc/stm32_assert.h          Template file to include assert_failed function
  - I2C/I2C_OneBoard_Communication_IT/Src/stm32l1xx_it.c          Interrupt handlers
  - I2C/I2C_OneBoard_Communication_IT/Src/main.c                  Main program
  - I2C/I2C_OneBoard_Communication_IT/Src/system_stm32l1xx.c      STM32L1xx system source file

@par Hardware and Software environment

  - This example runs on STM32L152xE devices.
    
  - This example has been tested with STM32L152RE-Nucleo Rev C board and can be
    easily tailored to any other supported device and development board.

  - STM32L152RE-Nucleo Rev C Set-up
    - Connect GPIOs connected to I2C1 SCL/SDA (PB.6 and PB.7)
    to respectively SCL and SDA pins of I2C2 (PB.10 and PB.11).
      - I2C1_SCL  PB.6 (CN10, pin 17) : connected to I2C2_SCL PB.10 (CN10, pin 25) 
      - I2C1_SDA  PB.7 (CN7, pin 21) : connected to I2C2_SDA PB.11 (CN10, pin 18)

  - Launch the program. Press User push-button to initiate a read request by Master 
      then Slave send a byte.
  - User can easily change the number of data to transfer by modifying
      the initialization of variables ubNbDataToTransmit and ubNbDataToReceive.

@par How to use it ? 

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
