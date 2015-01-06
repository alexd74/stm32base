#ifndef SCM_CUSTOM_INIT

#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx) || defined (STM32F411xE)
#include "stm32f4xx.h"
#else
#include "stm32f10x.h"
#endif

void initScmRTOS(void)  __attribute__ ((constructor, used));

void initScmRTOS(void)
{
#if defined (STM32F40_41xxx) || defined (STM32F427_437xx) || defined (STM32F429_439xx) || defined (STM32F401xx) || defined (STM32F411xE)

	// enable GPIOx peripherals
	RCC->AHB1ENR |=
			0
			| RCC_AHB1ENR_GPIOAEN
			| RCC_AHB1ENR_GPIOBEN
			| RCC_AHB1ENR_GPIOCEN
			| RCC_AHB1ENR_GPIODEN
			| RCC_AHB1ENR_GPIOEEN
			| RCC_AHB1ENR_GPIOFEN
			| RCC_AHB1ENR_GPIOGEN
			| RCC_AHB1ENR_GPIOHEN
			| RCC_AHB1ENR_GPIOIEN
			;
#else
  // enable IOPx periph
  RCC->APB2ENR |=
    RCC_APB2ENR_IOPAEN |
    RCC_APB2ENR_IOPBEN |
    RCC_APB2ENR_IOPCEN |
    RCC_APB2ENR_IOPDEN |
#ifdef RCC_APB2ENR_IOPEEN
    RCC_APB2ENR_IOPEEN |
#endif
    RCC_APB2ENR_AFIOEN;

#endif

  // Настраиваем приоритеты прерываний.
  // 15- самый низкий приоритет.
  // 0 - самый высокий приоритет.
  //
  // PRIGROUP
  // 0x7 - оброботчик прерывания может быть прерван любым более приоритетным прерыванием.
  // 0x6 - оброботчик прерывания может быть прерван другим прерыванием, более приоритетным из
  //          другой группы. (0-7 первая группа, 8-16 вторая группа)
  // 0x3 - каждый обработчик прерывания может быть прерван другим, более приоритетным, прерыванием.
  //
  //    PRIGROUP      группы (с вытеснением)      подгруппы
  //       0x3                 16                  0
  //       0x4                  8                  2
  //       0x5                  4                  4
  //       0x6                  2                  8
  //       0x7                  0                 16

  //	NVIC_SetPriorityGrouping(7);	// no preemption, 4 bit of subprio
  // NVIC_SetPriorityGrouping(6);	// 1 bit preemption, 3 bit of subprio
  NVIC_SetPriorityGrouping(5);	// 2 bit preemption, 2 bit of subprio
  //	NVIC_SetPriorityGrouping(4);	// 3 bit preemption, 1 bit of subprio
  //	NVIC_SetPriorityGrouping(3);	// 4 bit preemption, 0 bit of subprio
}

#endif
