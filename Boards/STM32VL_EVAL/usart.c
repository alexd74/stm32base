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
  while ((USART1->SR & USART_SR_TC) == (uint16_t) RESET) { }

  USART1->DR = (unsigned char) ch;

  return ch;
}

int usart_getchar()
{
  while ((USART1->SR & USART_SR_RXNE) == (uint16_t) RESET) {}

  return (char) (USART1->DR & (uint16_t) 0x01FF);
}

const unsigned int PCLK_FREQUENCY = 24000000UL;

#if 0
void init_usart( int baudrate )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef  USART_ClockInitStructure;

	//enable bus clocks
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

	//Set USART1 Tx (PA.09) as AF push-pull
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//Set USART1 Rx (PA.10) as input floating
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_ClockStructInit(&USART_ClockInitStructure);
	USART_ClockInit(USART1, &USART_ClockInitStructure);

	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	//Write USART1 parameters
	USART_Init(USART1, &USART_InitStructure);

	//Enable USART1
	USART_Cmd(USART1, ENABLE);
}
#else
void init_usart( int baudrate )
{
/*	GPIO_InitTypeDef GPIO_InitStructure;*/

  USART1->CR1 &= ~USART_CR1_UE;

  /* Enable GPIO clock */
  RCC->APB2ENR |= RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN;

  uint32_t tmpreg = GPIOA->CRH;
  tmpreg &= ~( GPIO_CRL_MODE2 | GPIO_CRL_CNF2 | GPIO_CRL_MODE1 | GPIO_CRL_CNF1 );

  /* Configure USART Rx as input floating */
  tmpreg |= /* pin 10 as in floating*/           0x04 << ( 4 * ( 10 - 8 ) ) |
  /* Configure USART Tx as alternate function push-pull */
            /*pin 9 as AF_PP speed 50Mhz */      0x0B << ( 4 * ( 9 - 8 ) );

  GPIOA->CRH = tmpreg;

  // no flow control
  USART1->CR3 = 0;
  // one stop bit
  USART1->CR2 = 0;
  // 8 bit word length, no parity, no interrupts,  enable RX and TX
  USART1->CR1 = USART_CR1_RE | USART_CR1_TE;
  // calculate baudrate register
  USART1->BRR = ( PCLK_FREQUENCY + baudrate / 2 ) / baudrate;

  /* Enable the  USART by setting the UE bit in the CR1 register */
  USART1->CR1 |= USART_CR1_UE;
}
#endif

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
