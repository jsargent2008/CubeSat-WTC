/**
  @page TouchSensing_Linear_hwacq  Touch Sensing Linear HW acquisition example
  
  @verbatim
  ******************** (C) COPYRIGHT 2017 STMicroelectronics *******************
  * @file    readme.txt
  * @author  MCD Application Team
  * @brief   Description of the Touch Sensing Linear example.
  ******************************************************************************
  *@attention
  *
  * <h2><center>&copy; Copyright © 2017 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  @endverbatim

@par Application Description

This firmware is a basic example on how to use the STMTouch driver with 1 linear
sensor using the hardware acquisition.

Observed behaviour:

- The LED1, LED2, LED3 and LED4 follow the linear sensor position when touched.

@par Directory contents

    - TouchSensing_Linear_hwacq\Inc\main.h                Header for main.c file
    - TouchSensing_Linear_hwacq\Inc\stm32l1xx_hal_conf.h  HAL Library configuration file
    - TouchSensing_Linear_hwacq\Inc\stm32l1xx_it.h        Header for stm32l1xx_it.c file
    - TouchSensing_Linear_hwacq\Src\stmCriticalSection.h  Header for stmCriticalSection.c file
    - TouchSensing_Linear_hwacq\Inc\tsl_conf.h            STMTouch driver configuration file
    - TouchSensing_Linear_hwacq\Inc\tsl_user.h            Header for tsl_user.c file

    - TouchSensing_Linear_hwacq\Src\main.c                Main program file
    - TouchSensing_Linear_hwacq\Src\stm32l1xx_hal_msp.c   HAL MSP module file
    - TouchSensing_Linear_hwacq\Src\stm32l1xx_it.c        Interrupt handlers file
    - TouchSensing_Linear_hwacq\Src\stmCriticalSection.c  STMStudio lock/unlock mechanism file
    - TouchSensing_Linear_hwacq\Src\system_stm32l1xx.c    System initialization file
    - TouchSensing_Linear_hwacq\Src\tsl_user.c            Touchsensing channels/banks description file

@par Hardware and Software environment

  - This example runs on STM32L152xD devices.

  - This example has been tested with STM32L152D-EVAL
    boards and can be easily tailored to any other supported device
    and development board.

  @note Make sure that LCD Glass is in IO position
  
@par How to use it ?

In order to make the program work, you must do the following :
 - Open your preferred toolchain
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT STMicroelectronics</center></h3>
 */
