/**
*  GPIO pin manipulation class template for STM32 series.
*
*  Copyright (c) 2009-2012 Anton Gusev aka AHTOXA (HTTP://AHTOXA.NET)
*
*  Inspired by AVR macros from Askold Volkov
*
* USAGE: see corresponding include file
*
*  Public domain, AS IS.
*
*/

#ifndef PIN_H_INCLUDED
#define PIN_H_INCLUDED

#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx) || defined (STM32F411xE)
#  include "pin_stm32F4xx.h"
#else
#  include "pin_stm32F1xx.h"
#endif

#endif // PIN_H_INCLUDED
