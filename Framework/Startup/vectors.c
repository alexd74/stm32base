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
#elif defined STM32F4
#include "vectors_F4.c"
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
