#ifndef SCM_CUSTOM_INIT

#include "stm32f10x.h"

void initScmRTOS(void)  __attribute__ ((constructor, used));

void initScmRTOS(void)
{
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

  // ����������� ���������� ����������.
  // 15- ����� ������ ���������.
  // 0 - ����� ������� ���������.
  //
  // PRIGROUP
  // 0x7 - ���������� ���������� ����� ���� ������� ����� ����� ������������ �����������.
  // 0x6 - ���������� ���������� ����� ���� ������� ������ �����������, ����� ������������ ��
  //          ������ ������. (0-7 ������ ������, 8-16 ������ ������)
  // 0x3 - ������ ���������� ���������� ����� ���� ������� ������, ����� ������������, �����������.
  //
  //    PRIGROUP      ������ (� �����������)      ���������
  //       0x3                 16                  0
  //       0x4                  8                  2
  //       0x5                  4                  4
  //       0x6                  2                  8
  //       0x7                  0                 16

  //	NVIC_SetPriorityGrouping(7);	// no preemption, 4 bit of subprio
  NVIC_SetPriorityGrouping(6);	// 1 bit preemption, 3 bit of subprio
  //	NVIC_SetPriorityGrouping(5);	// 2 bit preemption, 2 bit of subprio
  //	NVIC_SetPriorityGrouping(4);	// 3 bit preemption, 1 bit of subprio
  //	NVIC_SetPriorityGrouping(3);	// 4 bit preemption, 0 bit of subprio
}

#endif
