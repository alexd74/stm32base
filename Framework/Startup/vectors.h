#ifndef STM32F10x_IT_VECTORS_H
#define STM32F10x_IT_VECTORS_H

#define WEAK __attribute__ ((weak))

#ifdef __cplusplus
 extern "C" {
#endif

void WEAK NMI_Handler(void);
void WEAK HardFault_Handler(void);
void WEAK MemManage_Handler(void);
void WEAK BusFault_Handler(void);
void WEAK UsageFault_Handler(void);
void WEAK SVC_Handler(void);
void WEAK DebugMon_Handler(void);

#ifdef SCMRTOS
void WEAK PendSVC_ISR(void);
void WEAK SystemTimer_ISR(void);
#else
void WEAK PendSV_Handler(void);
void WEAK SysTick_Handler(void);
#endif

#if defined STM32F10X_LD
#include "vectors_LD.h"
#elif defined STM32F10X_LD_VL
#include "vectors_LD_VL.h"
#elif defined STM32F10X_CL
#include "vectors_CL.h"
#elif defined STM32F4
#include "vectors_F4.h"
#else
#error "Unknown processor"
#endif

#ifdef __cplusplus
}
#endif

#endif /* STM32F10x_IT_VECTORS_H */
