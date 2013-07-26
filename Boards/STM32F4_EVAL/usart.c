/*! {{{ File head comment
  \file usart.c

  \brief

 }}} */

#include <usart.h>

#include <stdio.h>

#include <stm32f4xx.h>
#include <stm32f4xx_usart.h>

int usart_putchar( int ch )
{
  // wait for usart free
  while ((USART2->SR & USART_FLAG_TC) == (uint16_t) RESET) { }

  USART2->DR = (unsigned char) ch;

  return ch;
}

int usart_getchar()
{
  while ((USART2->SR & USART_FLAG_RXNE) == (uint16_t) RESET) {}

  return (char) (USART2->DR & (uint16_t) 0x01FF);
}

void init_usart( int speed )
{
	USART_InitTypeDef USART_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

	// Clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	// IO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

	USART_InitStructure.USART_BaudRate = speed;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

	USART_Init(USART2, &USART_InitStructure);

	// Enable
	USART_Cmd( USART2, ENABLE );
}

#ifdef USART_RETARGET

void usart_auto_init()  __attribute__ ((constructor, used));

void usart_auto_init()
{
  init_usart( 115200 );
}

#if USART_RETARGET == MINI

#undef putchar
#undef getchar

inline int putchar( int ch )
{
  return usart_putchar( ch );
}

int getchar()
{
  return usart_getchar();
}

#endif

#endif
