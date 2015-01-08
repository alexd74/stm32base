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

void WEAK PendSV_Handler(void);
void WEAK SysTick_Handler(void);

#if defined STM32F10X_LD
#include "vectors_LD.h"
#elif defined STM32F10X_LD_VL
#include "vectors_LD_VL.h"
#elif defined STM32F10X_CL
#include "vectors_CL.h"
#elif defined STM32F40_41xxx
#include "vectors_F40_41X.h"
#elif defined STM32F429_439xx
#include "vectors_F429.h"
#else
#error "Unknown processor"
#endif

#ifdef __cplusplus
}
#endif

#endif /* STM32F10x_IT_VECTORS_H */
