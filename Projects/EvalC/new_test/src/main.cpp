#include "main.h"
#include <stdio.h>

#define MESSAGE1   " STM32 Connectivity "
#define MESSAGE2   " Line Device running"
#define MESSAGE3   " on STM3210C-EVAL   "

/* Private variables ---------------------------------------------------------*/
// USART_InitTypeDef USART_InitStructure;

GPIO_InitTypeDef GPIO_InitStructure;
static __IO uint32_t TimingDelay;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

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

  /* Retarget the C library printf function to the USARTx, can be USART1 or USART2
     depending on the EVAL board you are using ********************************/
  printf("\n\r %s", MESSAGE1);
  printf(" %s", MESSAGE2);
  printf(" %s\n\r", MESSAGE3);

  printf("BRR %d\n\r", USART2->BRR );

//	int *arr = new(std::nothrow) int[20];
	int *arr = new int[20];

  int val = reinterpret_cast<int>( arr );
  printf( "new pointer result = %d\n\r", val );
  printf( "new pointer result = %p\n\r", static_cast<void*>( arr ) );

  if( val == 0 )
  {
    printf( "new error\n\r" );
  }
  else
  {
    printf( "new OK\n\r" );

    for (int i = 0; i < 20; i++)
      arr[i] = i;

    delete[] arr;
    printf( "delete OK\n\r" );
  }

	Delay(200);

  while (1)
  {
    Delay( 1000 );

    printf( "test\n\r" );
  }
}

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
