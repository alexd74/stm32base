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
//          sleep(400);
          sleep(SLEEP_TIME);
          LED_GREEN.Off();

          Proc1Rec.signal();
        }
    }
}

void OS::system_timer_user_hook()
{
//    PB1.On();
//    TimerEvent.signal_isr();
}

#if scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook()
{
	__WFI();
}
#endif
