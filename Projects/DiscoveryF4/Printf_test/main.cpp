/**
*****************************************************************************
**
**  File        : main.c
**
**  Abstract    : main function.
**
**  Functions   : main
**
**  Environment : Atollic TrueSTUDIO(R)
**                STMicroelectronics STM32F4xx Standard Peripherals Library
**
**  Distribution: The file is distributed “as is,” without any warranty
**                of any kind.
**
**  (c)Copyright Atollic AB.
**  You may use this file as-is or modify it according to the needs of your
**  project. Distribution of this file (unmodified or modified) is not
**  permitted. Atollic AB permit registered Atollic TrueSTUDIO(R) users the
**  rights to distribute the assembled, compiled & linked contents of this
**  file as part of an application binary file, provided that it is built
**  using the Atollic TrueSTUDIO(R) toolchain.
**
**
*****************************************************************************
*/

#include <stdio.h>
#include <usart.h>


void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}

int main(void)
{
  char ch[30];
/*  int32_t a1,a2;*/

  printf("\r\n USART1 Test \r\n");
  printf("Enter any text: ");

  for( int i = 0; i < 5; ++i )
    usart_putchar( usart_getchar() );

//  scanf("%s",ch);

//  printf("\r\nYou entered: ");
//  printf("%s\r\n",ch);

#if 0
  while (1)
  {
    printf("\r\nEnter first number: ");
    scanf("%ld",&a1);
    printf("%ld", a1);
    printf("\r\nEnter second number: ");
    scanf("%ld",&a2);
    printf("%ld\r\n", a2);
    printf("Sum: %ld + %ld = %ld\r\n",a1, a2, a1 + a2);
    //interrupts does the job
  }
#endif

#if 1
  while(1)
  {
    printf("test!");
    Delay(9000000);
    printf("\n\r");
  }
#endif

}
