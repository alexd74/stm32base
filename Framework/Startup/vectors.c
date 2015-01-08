/*

Copyright (c) 2012 Alexey Dyachenko <alexd@inbox.ru>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

*/


#include "vectors.h"


extern unsigned long _etext;
extern unsigned long _sidata;
extern unsigned long _sdata;
extern unsigned long _edata;
extern unsigned long _sbss;
extern unsigned long _ebss;
extern unsigned long _estack;
extern unsigned long __ctors_start__;
extern unsigned long __ctors_end__;

extern unsigned long __dtors_start__;
extern unsigned long __dtors_end__;

void Reset_Handler(void) __attribute__((__interrupt__));

/******************************************************************************
*
* The minimal vector table for a Cortex M3.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
typedef void( *const intfunc )( void );

#if defined STM32F10X_LD
#include "vectors_LD.c"
#elif defined STM32F10X_LD_VL
#include "vectors_LD_VL.c"
#elif defined STM32F10X_CL
#include "vectors_CL.c"
#elif defined STM32F40_41xxx
#include "vectors_F40_41X.c"
#elif defined STM32F429_439xx
#include "vectors_F429.c"
#else
#error "Unknown processor"
#endif

// {{{ Weak pragmas default handler

/*******************************************************************************
*
* Provide weak aliases for each Exception handler to the Default_Handler.
* As they are weak aliases, any function with the same name will override
* this definition.
*
*******************************************************************************/

#ifdef MINI_STARTUP

#pragma weak MMI_Handler = Default_Handler
#pragma weak MemManage_Handler = Default_Handler
#pragma weak BusFault_Handler = Default_Handler
#pragma weak UsageFault_Handler = Default_Handler
#pragma weak SVC_Handler = Default_Handler
#pragma weak DebugMon_Handler = Default_Handler
#pragma weak PendSV_Handler = Default_Handler

#else


#pragma weak NMI_Handler  = NMI_HandlerDefault
#pragma weak HardFault_Handler  = HardFault_HandlerDefault
#pragma weak MemManage_Handler = MemManage_HandlerDefault
#pragma weak BusFault_Handler = BusFault_HandlerDefault
#pragma weak UsageFault_Handler = UsageFault_HandlerDefault
#pragma weak SVC_Handler  = SVC_HandlerDefault
#pragma weak DebugMon_Handler  = DebugMon_HandlerDefault
#pragma weak PendSV_Handler  = PendSV_HandlerDefault

void NMI_HandlerDefault(void)
{
}

void HardFault_HandlerDefault(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

void MemManage_HandlerDefault(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

void BusFault_HandlerDefault(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

void UsageFault_HandlerDefault(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}


void SVC_HandlerDefault(void)
{
}

void DebugMon_HandlerDefault(void)
{
}

void PendSV_HandlerDefault(void)
{
}





#endif
//}}}

#pragma weak SysTick_Handler = Default_Handler


void Default_Handler(void)
{
    for (;;);
}

//}}}


/* {{{ Modeline for ViM
 *  * vim600:fdm=marker fdls=0 fdc=3 ts=4 shiftwidth=4:
 *   * }}} */
