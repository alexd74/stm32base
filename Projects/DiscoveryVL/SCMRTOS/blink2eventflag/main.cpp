//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M3 
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: 4.00
//*
//*     $Revision: 546 $
//*     $Date:: 2012-05-15 #$
//*
//*     Copyright (c) 2003-2012, Harry E. Zhurov
//*
//*     Permission is hereby granted, free of charge, to any person 
//*     obtaining  a copy of this software and associated documentation 
//*     files (the "Software"), to deal in the Software without restriction, 
//*     including without limitation the rights to use, copy, modify, merge, 
//*     publish, distribute, sublicense, and/or sell copies of the Software, 
//*     and to permit persons to whom the Software is furnished to do so, 
//*     subject to the following conditions:
//*
//*     The above copyright notice and this permission notice shall be included 
//*     in all copies or substantial portions of the Software.
//*
//*     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
//*     EXPRESS  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
//*     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
//*     IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
//*     CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
//*     TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
//*     THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//*
//*     =================================================================
//*     See http://scmrtos.sourceforge.net for documentation, latest
//*     information, license and contact details.
//*     =================================================================
//*
//******************************************************************************
//*     gcc port by Anton B. Gusev aka AHTOXA, Copyright (c) 2009-2012
//
// port to STM32VLDiscovery boart by Alexey Dyachenko, Copyright (c) 2012

#include "stm32f10x.h"
#include "IO/pin.h"
#include <scmRTOS.h>

#define SLEEP_TIME 500

//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 300> TProc1;
typedef OS::process<OS::pr1, 300> TProc2;
//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;

OS::TEventFlag Proc1Rec;
OS::TEventFlag Proc2Rec;

//---------------------------------------------------------------------------
//
//      IO Pins
//
Pin<'C', 9> LED_GREEN;
Pin<'C', 8> LED_BLUE;

int main()
{
    // configure IO pins
    LED_GREEN.Direct(OUTPUT);
    LED_GREEN.Off();
    LED_BLUE.Direct(OUTPUT);
    LED_BLUE.Off();

    Proc1Rec.signal();

    // run
    OS::run();
}

namespace OS
{
    template <>
    OS_PROCESS void TProc1::exec()
    {
        for(;;)
        {
          Proc1Rec.wait();

          LED_BLUE.On();
          sleep(SLEEP_TIME);
          LED_BLUE.Off();

          Proc2Rec.signal();
        }
    }

    template <>
    OS_PROCESS void TProc2::exec()
    {
        for(;;)
        {
          Proc2Rec.wait();

          LED_GREEN.On();
          sleep(SLEEP_TIME);
          LED_GREEN.Off();

          Proc1Rec.signal();
        }
    }
}

void OS::system_timer_user_hook()
{
}

#if scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook()
{
	__WFI();
}
#endif
