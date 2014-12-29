//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PURPOSE:  OS Kernel Header. Declarations And Definitions
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
//*****************************************************************************

#ifndef OS_KERNEL_H
#define OS_KERNEL_H

#include <stddef.h>
#include <stdint.h>
#include <usrlib.h>

//------------------------------------------------------------------------------

//==============================================================================
extern "C" NORETURN void os_start(stack_item_t* sp);

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
extern "C" void os_context_switcher(stack_item_t** Curr_SP, stack_item_t* Next_SP);
#else
extern "C" stack_item_t* os_context_switch_hook(stack_item_t* sp);
#endif


#if scmRTOS_OBSOLETE_NAMES == 1

INLINE void OS_Start(stack_item_t* sp) { os_start(sp); }

#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
INLINE void OS_ContextSwitcher(stack_item_t** Curr_SP, stack_item_t* Next_SP) { os_context_switcher(Curr_SP, Next_SP); }
#else
INLINE stack_item_t* OS_ContextSwitchHook(stack_item_t* sp) { return os_context_switch_hook(sp); }
#endif

#endif // scmRTOS_OBSOLETE_NAMES
    
//==============================================================================

//------------------------------------------------------------------------------
//
//
//     NAME       :   OS
//
//     PURPOSE    :   Namespace for all OS stuff
//
//     DESCRIPTION:   Includes:  Kernel,
//                               Processes,
//                               Mutexes,
//                               Event Flags,
//                               Byte-wide Channels,
//                               Arbitrary-type Channels,
//                               Messages
//
namespace OS
{
    
    const uint_fast8_t PROCESS_COUNT         = scmRTOS_PROCESS_COUNT + 1;
    const stack_item_t STACK_DEFAULT_PATTERN = scmRTOS_STACK_PATTERN;
    
    class TBaseProcess;

    INLINE void set_prio_tag(volatile TProcessMap & pm, const TProcessMap PrioTag) { pm |=  PrioTag; }
    INLINE void clr_prio_tag(volatile TProcessMap & pm, const TProcessMap PrioTag) { pm &= ~PrioTag; }
    INLINE void set_prio_tag(TProcessMap & pm, const TProcessMap PrioTag) { pm |=  PrioTag; }
    INLINE void clr_prio_tag(TProcessMap & pm, const TProcessMap PrioTag) { pm &= ~PrioTag; }

    
#if scmRTOS_OBSOLETE_NAMES == 1

    INLINE void SetPrioTag(volatile TProcessMap & pm, const TProcessMap PrioTag) { set_prio_tag(pm, PrioTag); }
    INLINE void ClrPrioTag(volatile TProcessMap & pm, const TProcessMap PrioTag) { clr_prio_tag(pm, PrioTag); }
    INLINE void SetPrioTag(TProcessMap & pm, const TProcessMap PrioTag) { set_prio_tag(pm, PrioTag); }
    INLINE void ClrPrioTag(TProcessMap & pm, const TProcessMap PrioTag) { clr_prio_tag(pm, PrioTag); }

#endif
    
    //--------------------------------------------------------------------------
    //
    //     NAME       :   TKernel
    //
    ///  Implements kernel-level operations such as
    ///  process management, process-level scheduling,
    ///  ISR-level scheduling, system timing.
    //
    //     DESCRIPTION:
    //
    //
    class TKernel
    {
        //-----------------------------------------------------------
        //
        //     Declarations
        //
        friend class TISRW;
        friend class TISRW_SS;
        friend class TBaseProcess;
        friend class TKernelAgent;
        
        friend void                 run();
        friend const TBaseProcess * get_proc(uint_fast8_t Prio);
    #if scmRTOS_SYSTEM_TICKS_ENABLE == 1
        friend inline tick_count_t  get_tick_count();
    #endif

        //-----------------------------------------------------------
        //
        //      Data
        //
    private:
        uint_fast8_t          CurProcPriority;
        volatile TProcessMap  ReadyProcessMap;
        static TBaseProcess*  ProcessTable[PROCESS_COUNT];
        volatile uint_fast8_t ISR_NestCount;

    #if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
        volatile uint_fast8_t SchedProcPriority;
    #endif

    #if scmRTOS_SYSTEM_TICKS_ENABLE == 1
        volatile tick_count_t SysTickCount;
    #endif

    //-----------------------------------------------------------
    //
    //      Functions
    //
    public:
    INLINE TKernel() : CurProcPriority(pr0)
                     , ReadyProcessMap( (1ul << (PROCESS_COUNT)) - 1)  // set all processes ready
                     , ISR_NestCount(0)
    {
    }
    
    private:
        INLINE static void register_process(TBaseProcess* const p);

               void sched();
        INLINE void scheduler() { if(ISR_NestCount) return; else  sched(); }
        INLINE void sched_isr();

    #if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
        INLINE bool is_context_switch_done();
        #if scmRTOS_OBSOLETE_NAMES == 0
        INLINE void raise_context_switch() { OS::raise_context_switch(); }
        #else
        INLINE void raise_context_switch() { OS::RaiseContextSwitch(); }
        #endif
    #endif
    
        INLINE void set_process_ready  (const uint_fast8_t pr) { TProcessMap PrioTag = get_prio_tag(pr); set_prio_tag( ReadyProcessMap, PrioTag); }
        INLINE void set_process_unready(const uint_fast8_t pr) { TProcessMap PrioTag = get_prio_tag(pr); clr_prio_tag( ReadyProcessMap, PrioTag); }

    public:
        INLINE void system_timer();
    #if scmRTOS_CONTEXT_SWITCH_SCHEME == 1
        INLINE stack_item_t* context_switch_hook(stack_item_t* sp);
    #endif
    };  // End of TKernel class definition

    extern TKernel Kernel;

    //--------------------------------------------------------------------------
    //
    //  BaseProcess
    // 
    //  Implements base class-type for application processes
    //
    //      DESCRIPTION:
    //
    //
    class TKernelAgent;
    class TService;

    class TBaseProcess
    {
        friend class TKernel;
        friend class TISRW;
        friend class TISRW_SS;
        friend class TKernelAgent;

        friend void run();

    public:
    #if SEPARATE_RETURN_STACK == 0

        TBaseProcess( stack_item_t * StackPoolEnd
                    , TPriority pr
                    , void (*exec)()
                #if scmRTOS_DEBUG_ENABLE == 1
                    , stack_item_t * aStackPool
                #endif
                    );

    protected:
        INLINE void set_unready() { Kernel.set_process_unready(this->Priority); }
        void init_stack_frame( stack_item_t * StackPoolEnd
                             , void (*exec)() 
        #if scmRTOS_DEBUG_ENABLE == 1
                             , stack_item_t * StackPool
        #endif
                             );
    public:

    #else  // SEPARATE_RETURN_STACK

        TBaseProcess( stack_item_t* StackPoolEnd
                    , stack_item_t* RStack
                    , TPriority pr
                    , void (*exec)() 
                #if scmRTOS_DEBUG_ENABLE == 1
                    , stack_item_t * aStackPool
                    , stack_item_t * aRStackPool
                #endif
                    );

    protected:
        void init_stack_frame( stack_item_t * Stack
                             , stack_item_t * RStack
                             , void (*exec)() 
        #if scmRTOS_DEBUG_ENABLE == 1
                             , stack_item_t * StackPool
                             , stack_item_t * RStackPool
        #endif
                             );
        
    public:

    #endif // SEPARATE_RETURN_STACK
        
        static void sleep(timeout_t timeout = 0);
               void wake_up();
               void force_wake_up();
        INLINE void start() { force_wake_up(); }

        INLINE bool is_sleeping() const;
        INLINE bool is_suspended() const;

    #if scmRTOS_DEBUG_ENABLE == 1
        INLINE TService * waiting_for() const { return WaitingFor; }
    public:
               size_t     stack_slack() const; 
        #if SEPARATE_RETURN_STACK == 1
               size_t     rstack_slack() const;
        #endif               
    #endif // scmRTOS_DEBUG_ENABLE

    #if scmRTOS_PROCESS_RESTART_ENABLE == 1
    protected:
               void reset_controls();
    #endif
    
    public:

    #if scmRTOS_OBSOLETE_NAMES == 1
        INLINE static void Sleep(timeout_t timeout = 0) { sleep(timeout); }
    #endif
    
        //-----------------------------------------------------
        //
        //    Data members
        //
    protected:
        stack_item_t *     StackPointer;
        volatile timeout_t Timeout;
        const TPriority    Priority;
    #if scmRTOS_DEBUG_ENABLE == 1
        TService           * volatile WaitingFor;
        const stack_item_t * const StackPool;
        #if SEPARATE_RETURN_STACK == 1
            const stack_item_t * const RStackPool;
        #endif
    #endif // scmRTOS_DEBUG_ENABLE
    
    #if scmRTOS_PROCESS_RESTART_ENABLE == 1
        volatile TProcessMap * WaitingProcessMap;
    #endif
    };
    //--------------------------------------------------------------------------

    //--------------------------------------------------------------------------
    //
    //   process
    // 
    //   Implements template for application processes instantiation
    //
    //      DESCRIPTION:
    //
    //
    #if SEPARATE_RETURN_STACK == 0

        template<TPriority pr, size_t stack_size>
        class process : public TBaseProcess
        {
        public:
            INLINE_PROCESS_CTOR process();

            OS_PROCESS static void exec();
            
        #if scmRTOS_PROCESS_RESTART_ENABLE == 1
            INLINE void terminate();
        #endif
            

        private:
            stack_item_t Stack[stack_size/sizeof(stack_item_t)];
        };

        template<TPriority pr, size_t stack_size>
        OS::process<pr, stack_size>::process() : TBaseProcess( &Stack[stack_size/sizeof(stack_item_t)]
                                                             , pr
                                                             , reinterpret_cast<void (*)()>(exec) 
                                                         #if scmRTOS_DEBUG_ENABLE == 1
                                                             , Stack
                                                         #endif
                                                             )
        {
        }
        
        #if scmRTOS_PROCESS_RESTART_ENABLE == 1
        template<TPriority pr, size_t stack_size>
        void OS::process<pr, stack_size>::terminate()
        {
            TCritSect cs;
            
            reset_controls();
            init_stack_frame( &Stack[stack_size/sizeof(stack_item_t)]
                              , reinterpret_cast<void (*)()>(exec)
                          #if scmRTOS_DEBUG_ENABLE == 1
                              , Stack
                          #endif
                            );
        }
        #endif // scmRTOS_RESTART_ENABLE
        
        typedef OS::process<OS::prIDLE, scmRTOS_IDLE_PROCESS_STACK_SIZE> TIdleProc;

    #else  // SEPARATE_RETURN_STACK

        template<TPriority pr, size_t stack_size, size_t rstack_size>
        class process : public TBaseProcess
        {
        public:
            INLINE_PROCESS_CTOR process();

            OS_PROCESS static void exec();

        #if scmRTOS_PROCESS_RESTART_ENABLE == 1
            INLINE void terminate();
        #endif

        private:
            stack_item_t Stack [stack_size/sizeof(stack_item_t)];
            stack_item_t RStack[rstack_size/sizeof(stack_item_t)];
        };

        template<TPriority pr, size_t stack_size, size_t rstack_size>
        process<pr, stack_size, rstack_size>::process() : TBaseProcess( &Stack[stack_size/sizeof(stack_item_t)]
                                                                      , &RStack[rstack_size/sizeof(stack_item_t)]
                                                                      , pr
                                                                      , reinterpret_cast<void (*)()>(exec)
                                                                 #if scmRTOS_DEBUG_ENABLE == 1
                                                                      , Stack
                                                                      , RStack
                                                                 #endif
                                                                      )
        {
        }
        
        #if scmRTOS_PROCESS_RESTART_ENABLE == 1
        template<TPriority pr, size_t stack_size, size_t rstack_size>
        void OS::process<pr, stack_size, rstack_size>::terminate()
        {
            TCritSect cs;
            
            reset_controls();
            init_stack_frame( &Stack[stack_size/sizeof(stack_item_t)]
                            , &RStack[rstack_size/sizeof(stack_item_t)]
                            , reinterpret_cast<void (*)()>(exec)
                        #if scmRTOS_DEBUG_ENABLE == 1
                            , Stack
                            , RStack
                        #endif
                            );
        }
        #endif // scmRTOS_RESTART_ENABLE

        typedef OS::process< OS::prIDLE
                           , scmRTOS_IDLE_PROCESS_DATA_STACK_SIZE
                           , scmRTOS_IDLE_PROCESS_RETURN_STACK_SIZE> TIdleProc;

    #endif    // SEPARATE_RETURN_STACK
    //--------------------------------------------------------------------------


    extern TIdleProc IdleProc;
        
    //--------------------------------------------------------------------------
    //
    //   TKernelAgent
    // 
    //   Grants access to some RTOS kernel internals for services implementation
    //
    //      DESCRIPTION:
    //
    //
    class TKernelAgent
    {
        INLINE static TBaseProcess * cur_proc()                        { return Kernel.ProcessTable[cur_proc_priority()]; }

    protected:
        TKernelAgent() { }
        INLINE static uint_fast8_t const   & cur_proc_priority()       { return Kernel.CurProcPriority;  }
        INLINE static volatile TProcessMap & ready_process_map()       { return Kernel.ReadyProcessMap;  }
        INLINE static volatile timeout_t   & cur_proc_timeout()        { return cur_proc()->Timeout;     }
        INLINE static void reschedule()                                { Kernel.scheduler();             }

    #if scmRTOS_DEBUG_ENABLE == 1
        INLINE static TService * volatile & cur_proc_waiting_for()     { return cur_proc()->WaitingFor;  }
    #endif
    
    #if scmRTOS_PROCESS_RESTART_ENABLE == 1
        INLINE static volatile TProcessMap * & cur_proc_waiting_map()  { return cur_proc()->WaitingProcessMap; }
    #endif
    };
    
    //--------------------------------------------------------------------------
    //
    //       Miscellaneous
    //
    //
    INLINE NORETURN void run();
    INLINE void lock_system_timer()    { TCritSect cs; LOCK_SYSTEM_TIMER();   }
    INLINE void unlock_system_timer()  { TCritSect cs; UNLOCK_SYSTEM_TIMER(); }
    INLINE void sleep(timeout_t t = 0) { TBaseProcess::sleep(t); }
    INLINE const TBaseProcess * get_proc(uint_fast8_t Prio) { return Kernel.ProcessTable[Prio]; }
    
#if scmRTOS_OBSOLETE_NAMES == 1
    INLINE void Run()               { run();                 }
    INLINE void LockSystemTimer()   { lock_system_timer();   }
    INLINE void UnlockSystemTimer() { unlock_system_timer(); }
#endif        
    
    //--------------------------------------------------------------------------

#if scmRTOS_SYSTEM_TICKS_ENABLE == 1
    INLINE tick_count_t get_tick_count() { TCritSect cs; return Kernel.SysTickCount; }
#if scmRTOS_OBSOLETE_NAMES == 1
    INLINE tick_count_t GetTickCount() { return get_tick_count(); }
#endif
#endif

#if scmRTOS_TARGET_IDLE_HOOK_ENABLE == 1
    void idle_process_target_hook();
#endif // scmRTOS_TARGET_IDLE_HOOK_ENABLE

#if scmRTOS_OBSOLETE_NAMES == 1

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    INLINE_SYS_TIMER_HOOK void SystemTimerUserHook();
    INLINE void system_timer_user_hook() { SystemTimerUserHook(); }
#endif // scmRTOS_SYSTIMER_HOOK_ENABLE

#if scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE == 1
    INLINE_CONTEXT_SWITCH_HOOK void ContextSwitchUserHook();
    INLINE void context_switch_user_hook() { ContextSwitchUserHook(); }
#endif // scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE

#if scmRTOS_IDLE_HOOK_ENABLE == 1
    void IdleProcessUserHook();
    INLINE void idle_process_user_hook() { IdleProcessUserHook(); }
#endif // scmRTOS_IDLE_HOOK_ENABLE

#else // scmRTOS_OBSOLETE_NAMES

#if scmRTOS_SYSTIMER_HOOK_ENABLE == 1
    INLINE_SYS_TIMER_HOOK void system_timer_user_hook();
#endif // scmRTOS_SYSTIMER_HOOK_ENABLE

#if scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE == 1
    INLINE_CONTEXT_SWITCH_HOOK void context_switch_user_hook();
#endif // scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE

#if scmRTOS_IDLE_HOOK_ENABLE == 1
    void idle_process_user_hook();
#endif // scmRTOS_IDLE_HOOK_ENABLE

#endif // scmRTOS_OBSOLETE_NAMES

    
}   // namespace OS
//------------------------------------------------------------------------------

#include "scmRTOS_extensions.h"

//------------------------------------------------------------------------------
//
//   Register Process
// 
//   Places pointer to process in kernel's process table
//
void OS::TKernel::register_process(OS::TBaseProcess* const p)
{
    Kernel.ProcessTable[p->Priority] = p;
}
//------------------------------------------------------------------------------
//
//    System Timer Implementation
// 
//    Performs process's timeouts checking and
//    moving processes to ready-to-run state
//
void OS::TKernel::system_timer()
{
    SYS_TIMER_CRIT_SECT();
#if scmRTOS_SYSTEM_TICKS_ENABLE == 1
    SysTickCount++;
#endif

#if scmRTOS_PRIORITY_ORDER == 0
    const uint_fast8_t BaseIndex = 0;
#else
    const uint_fast8_t BaseIndex = 1;
#endif

    for(uint_fast8_t i = BaseIndex; i < (PROCESS_COUNT - 1 + BaseIndex); i++)
    {
        TBaseProcess* p = ProcessTable[i];

        if(p->Timeout > 0)
        {
            if(--p->Timeout == 0)
            {
                set_process_ready(p->Priority);
            }
        }
    }
}
//------------------------------------------------------------------------------
//
//     ISR optimized scheduler
// 
//     !!! IMPORTANT: This function must be call from ISR services only !!!
//
//
#if scmRTOS_CONTEXT_SWITCH_SCHEME == 0
void OS::TKernel::sched_isr()
{
    uint_fast8_t NextPrty = highest_priority(ReadyProcessMap);
    if(NextPrty != CurProcPriority)
    {
    #if scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE == 1
        context_switch_user_hook();
    #endif
    
        stack_item_t*  Next_SP = ProcessTable[NextPrty]->StackPointer;
        stack_item_t** Curr_SP_addr = &(ProcessTable[CurProcPriority]->StackPointer);
        CurProcPriority = NextPrty;
        os_context_switcher(Curr_SP_addr, Next_SP);
    }
}
#else
void OS::TKernel::sched_isr()
{
    uint_fast8_t NextPrty = highest_priority(ReadyProcessMap);
    if(NextPrty != CurProcPriority)
    {
        SchedProcPriority = NextPrty;
        raise_context_switch();
    }
}
//------------------------------------------------------------------------------
#ifndef CONTEXT_SWITCH_HOOK_CRIT_SECT
#define CONTEXT_SWITCH_HOOK_CRIT_SECT()
#endif

stack_item_t* OS::TKernel::context_switch_hook(stack_item_t* sp)
{
    CONTEXT_SWITCH_HOOK_CRIT_SECT();

    ProcessTable[CurProcPriority]->StackPointer = sp;
    sp = ProcessTable[SchedProcPriority]->StackPointer;
    
#if scmRTOS_CONTEXT_SWITCH_USER_HOOK_ENABLE == 1
    context_switch_user_hook();
#endif

    CurProcPriority = SchedProcPriority;
    return sp;
}
//------------------------------------------------------------------------------
#endif // scmRTOS_CONTEXT_SWITCH_SCHEME

//-----------------------------------------------------------------------------
bool OS::TBaseProcess::is_sleeping() const
{
    TCritSect cs;
    return this->Timeout != 0;
}
//-----------------------------------------------------------------------------
bool OS::TBaseProcess::is_suspended() const
{
    TCritSect cs;
    return (Kernel.ReadyProcessMap & get_prio_tag(this->Priority)) == 0;
}

//-----------------------------------------------------------------------------
INLINE void OS::run()
{
    stack_item_t *sp = Kernel.ProcessTable[pr0]->StackPointer;
    os_start(sp);
}

#if scmRTOS_OBSOLETE_NAMES == 1
namespace OS
{
    INLINE void Sleep(timeout_t t = 0) { sleep(t); }

    INLINE bool IsProcessSleeping(const TBaseProcess& p) { return p.is_sleeping(); }
    INLINE bool IsProcessSuspended(const TBaseProcess& p) { return p.is_suspended(); }
}   // namespace OS
#endif

#include <OS_Services.h>

#endif // OS_KERNEL_H
