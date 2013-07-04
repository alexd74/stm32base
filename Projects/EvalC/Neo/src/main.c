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

#ifdef USE_STM3210B_EVAL
 #include "stm3210b_eval_lcd.h"
#elif defined USE_STM3210E_EVAL
 #include "stm3210e_eval_lcd.h"
#elif defined USE_STM3210C_EVAL
 #include "stm3210c_eval_lcd.h"
#endif

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#ifdef USE_STM3210B_EVAL
  #define MESSAGE1   "STM32 Medium Density"
  #define MESSAGE2   " Device running on  "
  #define MESSAGE3   "   STM3210B-EVAL    "
#elif defined USE_STM3210E_EVAL
  #define MESSAGE1   " STM32 High Density "
  #define MESSAGE2   " Device running on  "
  #define MESSAGE3   "   STM3210E-EVAL    "
#elif defined USE_STM3210C_EVAL
  #define MESSAGE1   " STM32 Connectivity "
  #define MESSAGE2   " Line Device running"
  #define MESSAGE3   " on STM3210C-EVAL   "
#endif

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
 USART_InitTypeDef USART_InitStructure;

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

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Inserts a delay time.
  * @param  nCount: specifies the delay time length.
  * @retval None
  */
#if 0
void Delay(__IO uint32_t nCount)
{
  nCount *= 10000;
  for(; nCount != 0; nCount--);
}
#endif


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /* Setup STM32 system (clock, PLL and Flash configuration) */
  SystemInit();

  /* Initialize LEDs, Key Button, LCD and COM port(USART) available on
     STM3210X-EVAL board ******************************************************/
  STM_EVAL_LEDInit(LED1);
  STM_EVAL_LEDInit(LED2);
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);

  /* Setup SysTick Timer for 1 msec interrupts  */
  if (SysTick_Config( SystemCoreClock / 1000))
  {
    /* Capture error */
    while (1);
  }

  /* USARTx configured as follow:
        - BaudRate = 115200 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  STM_EVAL_COMInit(COM1, &USART_InitStructure);

  /* Initialize the LCD */
#ifdef USE_STM3210B_EVAL
  STM3210B_LCD_Init();
#elif defined USE_STM3210E_EVAL
  STM3210E_LCD_Init();
#elif defined USE_STM3210C_EVAL
  STM3210C_LCD_Init();
#endif

  /* Display message on STM3210X-EVAL LCD *************************************/
  /* Clear the LCD */
  LCD_Clear(Black);

  /* Set the LCD Back Color */
  LCD_SetBackColor(Black);
  /* Set the LCD Text Color */
  LCD_SetTextColor(Green);
  /*
  LCD_DisplayStringLine(Line0, MESSAGE1);
  LCD_DisplayStringLine(Line1, MESSAGE2);
  LCD_DisplayStringLine(Line2, MESSAGE3);
  */
//  LCD_DisplayStringLine(Line0, "Testprojekt : 1");
//  LCD_DisplayStringLine(Line3, "Thomas ist eine Held");

  STM_EVAL_LEDOff(LED1);
  STM_EVAL_LEDOff(LED2);
  STM_EVAL_LEDOff(LED3);
  STM_EVAL_LEDOff(LED4);

#if 1

  LCD_DisplayStringLine(Line0, "wake up, Neo...");

  Delay(1000);
  LCD_DisplayStringLine(Line2, "   MATRIX HAS YOU...");

  Delay(2000);

  LCD_DisplayStringLine(Line4, "follow" );
  LCD_DisplayStringLine(Line5, "  the white rabbit");


  /* Retarget the C library printf function to the USARTx, can be USART1 or USART2
     depending on the EVAL board you are using ********************************/
/*  printf("\n\r %s", MESSAGE1);*/
/*  printf(" %s", MESSAGE2);*/
/*  printf(" %s\n\r", MESSAGE3);*/

  /* Turn on leds available on STM3210X-EVAL **********************************/
/*  STM_EVAL_LEDOn(LED1);
  STM_EVAL_LEDOn(LED2);
  STM_EVAL_LEDOn(LED3);
  STM_EVAL_LEDOn(LED4);
*/

  Delay(2000);

  LCD_DisplayStringLine(Line7, " knock, knock, Neo");

  STM_EVAL_LEDOn(LED1);
  STM_EVAL_LEDOn(LED2);
  STM_EVAL_LEDOn(LED3);
  STM_EVAL_LEDOn(LED4);

  /* Add your application code here
     */
#endif

  while (1)
  {
    /* Toggle LED2 and LED4 */
    STM_EVAL_LEDToggle(LED2);
    STM_EVAL_LEDToggle(LED4);

    /* Insert 50 ms delay */
    Delay(200);

    /* Toggle LED1 and LED3 */
    STM_EVAL_LEDToggle(LED1);
    STM_EVAL_LEDToggle(LED3);

    /* Insert 100 ms delay */
    Delay(400);
  }
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(EVAL_COM1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(EVAL_COM1, USART_FLAG_TC) == RESET)
  {}

  return ch;
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

/**
  * @}
  */


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
