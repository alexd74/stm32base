/*! {{{ File head comment
  \file usart.c

  \brief

 }}} */

#include <usart.h>

#include <stdio.h>

#include <stm32f10x.h>
#include <stm32f10x_usart.h>

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

const unsigned int PCLK_FREQUENCY = 36000000UL;

void init_usart( int baudrate )
{
  GPIO_InitTypeDef GPIO_InitStructure;

  USART2->CR1 &= ~USART_CR1_UE;

  /* Enable GPIO clock */
/*  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE );*/
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPDEN;

    /* Enable the USART2 Pins Software Remapping */
/*  GPIO_PinRemapConfig( GPIO_Remap_USART2, ENABLE );*/

  AFIO->MAPR |= AFIO_MAPR_USART2_REMAP;

/*  RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2, ENABLE );*/
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init( GPIOD, &GPIO_InitStructure );

  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init( GPIOD, &GPIO_InitStructure );

  // no flow control
  USART2->CR3 = 0;
  // one stop bit
  USART2->CR2 = 0;
  // 8 bit word length, no parity, no interrupts,  enable RX and TX
  USART2->CR1 = USART_CR1_RE | USART_CR1_TE;
  // calculate baudrate register
  USART2->BRR = ( PCLK_FREQUENCY + baudrate / 2 ) / baudrate;

  /* Enable the  USART by setting the UE bit in the CR1 register */
  USART2->CR1 |= USART_CR1_UE;
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
