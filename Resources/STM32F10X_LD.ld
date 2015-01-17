/*************************************************
* linker script for ST32F100  microcontroller
************************************************/ 

MEMORY
{
	RAM (xrw)	: ORIGIN = 0x20000000, LENGTH =  8K
	FLASH (rx)	: ORIGIN = 0x08000000, LENGTH = 128K
}

INCLUDE STM32COMMON.ld
