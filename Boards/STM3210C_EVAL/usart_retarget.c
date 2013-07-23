/*! {{{ File head comment
  \file usart.c

  \brief

 }}} */

#include <stdio.h>

#include <stm32f10x.h>
#include <stm32f10x_usart.h>

#undef putchar
#undef getchar

int putchar( int ch )
{
  // wait for usart free
  while ((USART2->SR & USART_FLAG_TC) == (uint16_t) RESET) { }

  USART2->DR = (unsigned char) ch;

  return ch;
}

int getchar()
{
  while ((USART2->SR & USART_FLAG_RXNE) == (uint16_t) RESET) {}

  return (char) (USART2->DR & (uint16_t) 0x01FF);
}

void init_usart()  __attribute__ ((constructor, used));

void init_usart()
{
	USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE );

    /* Enable the USART2 Pins Software Remapping */
  GPIO_PinRemapConfig( GPIO_Remap_USART2, ENABLE );
  RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE );

  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( GPIOD, &GPIO_InitStructure );

  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init( GPIOD, &GPIO_InitStructure );

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* USART configuration */
  USART_Init( USART2, &USART_InitStructure );

  /* Enable the  USART by setting the UE bit in the CR1 register */
  USART2->CR1 |= USART_CR1_UE;
}
