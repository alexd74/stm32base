/*! {{{ File head comment
  \file usart.c

  \brief

 }}} */

#include <usart.h>

#include <stdio.h>

#include <stm32f10x.h>

int usart_putchar( int ch )
{
  // wait for usart free
  while ((USART2->SR & USART_SR_TC) == (uint16_t) RESET) { }

  USART2->DR = (unsigned char) ch;

  return ch;
}

int usart_getchar()
{
  while ((USART2->SR & USART_SR_RXNE) == (uint16_t) RESET) {}

  return (char) (USART2->DR & (uint16_t) 0x01FF);
}

const unsigned int PCLK_FREQUENCY = 36000000UL;

void init_usart( int baudrate )
{
  USART2->CR1 &= ~USART_CR1_UE;

  /* Enable GPIO clock */
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPDEN;

    /* Enable the USART2 Pins Software Remapping */
  AFIO->MAPR |= AFIO_MAPR_USART2_REMAP;

  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;


  uint32_t tmpreg = GPIOD->CRH;
  tmpreg &= ~( GPIO_CRL_MODE5 | GPIO_CRL_CNF5 | GPIO_CRL_MODE6 | GPIO_CRL_CNF6 );
  /* Configure USART Rx as input floating */
  tmpreg |= /* pin 6 as in floating*/           0x04 << ( 4 * 6 ) |
  /* Configure USART Tx as alternate function push-pull */
            /*pin 5 as AF_PP speed 50Mhz */     0x0B << ( 4 * 5 );

  GPIOD->CRH = tmpreg;

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
