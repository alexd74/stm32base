/**
  ******************************************************************************
  * @file    Project/Template/main.c
  * @author  MCD Application Team
  * @version V3.1.0
  * @date    06/19/2009
  * @brief   Main program body
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>

static __IO uint32_t TimingDelay;


void Delay(__IO uint32_t nTime);


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Setup SysTick Timer for 1 msec interrupts  */
  if (SysTick_Config( SystemCoreClock / 1000))
  {
    /* Capture error */
    while (1);
  }


  char ch[30];

  printf("\r\n USART1 Test \r\n");
  printf("Enter any text: ");
//  scanf("%s",ch);
  printf("\r\nYou entered: ");
  printf("%s\r\n",ch);

  while( 1 )
  {
    printf("test\r\n");
    Delay( 500 );
  }

#if 0
  int32_t a1,a2;

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
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while(TimingDelay != 0)
		;
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
