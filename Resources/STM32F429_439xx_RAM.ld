/*************************************************
* linker script for STM32F10x Connectivity Line Devices
************************************************/ 

MEMORY
{
	RAM (xrw)	: ORIGIN = 0x20000000, LENGTH =  192K
	FLASH (rx)	: ORIGIN = 0x08000000, LENGTH = 2048K
}

INCLUDE STM32COMMON_RAM.ld
