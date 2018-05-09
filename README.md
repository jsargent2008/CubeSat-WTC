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
 - Install [STM32CubeMX](http://www.st.com/en/development-tools/stsw-stm32095.html#getsoftware-scroll) Eclipse Add-on into Atollic
 	- Should be called "STSW-STM32095" or the like on ST's website. Use version **4.25+**
	 > Help, Install New Software, Add, Local

### Importing Projects
 - Be sure to download the **whole** repository into your workspace
 - Simply import the project you need
	 - File -> Import -> Existing Projects into Workspace, and then select the root folder location and add
	 - Don't worry about the libraries they are automatically linked
	 
### Creating New Projects
- In STMCube
	- Follow the instructions and configure the project as you see fit
	- Be sure to check "Generate under root"
	- Under Code Generator, **check Generate peripheral initialization as a pair of '.c/.h' files per peripheral**
	- Project -> Generate Code
- In Atollic
	- File -> Import -> Existing Projects into Workspace, and then select the root folder location and add
	- Add `WTC_Libs` library
		- Right click on the project -> Import -> File System
		- Navigate to the repo location in your workspace, select `WTC_Libs`
		- Check the `WTC_Libs` checkbox
		- Advanced -> Check Create links in workspace -> Finish
			> The path should be relative to PROJECT_LOC
	- Right click on the project -> C/C++ General -> Paths and Symbols -> Add 
		- Path is `${ProjDirPath}/../WTC_Libs`
		- Be sure to check add to all configurations and add to all languages

## Troubleshooting
 - `unknown type name 'HAL_StatusTypeDef'`   
 	This error occurs when you have a problem with order of includes, especially in the `WTC_Libs` library folder.

