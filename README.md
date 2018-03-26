# CubeSat-WTC
QPace/SurfSat WTC Code

## Structure
The code is structured into the following three folders:
 - Projects  
 
 	  |#|Project|Target|
    --- | --- | ---
    | 1 | [/WTC_Flight](WTC_Flight)       | STM32L151VE
    | 2 | [/WTC_Discovery](WTC_Discovery) | STM32L152RCTx
 - Source Libraries
 
 	  |#|Library|Target|
    --- | --- | --- 
    | 1 | [/WTC_Libs](WTC_Libs) | All

These first two are complete [STM32CubeMX](http://www.st.com/en/development-tools/stsw-stm32095.html#getsoftware-scroll) projects created in [Atollic TrueSTUDIO](https://atollic.com/truestudio/). While the third is merely a source folder. The first two projects use a linked source folder to access [/WTC_Libs](WTC_Libs) and its internal source code. 

Further project information is outlined below and in the respective folders. 

## Getting Started
### Setting up the IDE

 - Download  [Atollic TrueSTUDIO](https://atollic.com/truestudio/)
 - Install [STM32CubeMX](http://www.st.com/en/development-tools/stsw-stm32095.html#getsoftware-scroll) into Atollic
	 > Help, Install New Software, Add, Local

### Importing Projects
 - Be sure to download the **whole** repository into your workspace
 - Simply import the project you need
	 - Don't worry about the libraries they are automatically linked
## Troubleshooting
 - `unknown type name 'HAL_StatusTypeDef'`   
 	This error occurs when you have a problem with order of includes, especially in the `WTC_Libs` library folder.
