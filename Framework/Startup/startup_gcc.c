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
extern int main(void);
void __Init_Data(void);

#ifndef __STM32F10x_CONF_H
#ifndef __SYSTEM_STM32F4XX_H
void SystemInit(void);
#endif
#endif

void Reset_Handler(void)
{
  __Init_Data();

  main();
}

void __Init_Data(void)
{
  unsigned long *pulSrc, *pulDest;

  pulSrc = &_sidata;

  for(pulDest = &_sdata; pulDest < &_edata; )
    *(pulDest++) = *(pulSrc++);

  for(pulDest = &_sbss; pulDest < &_ebss; )
    *(pulDest++) = 0;

  // init hardware before calling constructors
  SystemInit();

  // Call constructors
  unsigned long *ctors;
  for(ctors = &__ctors_start__; ctors < &__ctors_end__; )
    ((void(*)(void))(*ctors++))();
}


/* {{{ Modeline for ViM
 *  vim600:fdm=marker fdls=0 fdc=3 ts=2 shiftwidth=2:
 * }}} */
