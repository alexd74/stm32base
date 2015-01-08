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

GPIO_InitTypeDef GPIO_InitStructure;
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

  /* LCD initialization */
  LCD_Init();

  /* LCD Layer initialization */
  LCD_LayerInit();

  /* Enable the LTDC */
  LTDC_Cmd(ENABLE);

  /* Set LCD foreground layer */
  LCD_SetLayer(LCD_FOREGROUND_LAYER);

  /* Clear the LCD */
  LCD_Clear(LCD_COLOR_BLACK);

  /* Set the LCD Back Color */
  LCD_SetBackColor(LCD_COLOR_BLACK);
  /* Set the LCD Text Color */
  LCD_SetTextColor(LCD_COLOR_GREEN);


  /* GPIOG Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

  /* Configure PD13 and PD14 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13| GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

  GPIO_ResetBits( GPIOG, GPIO_Pin_13|GPIO_Pin_14 );


  LCD_DisplayStringLine(LINE(0), "wake up, Neo...");

  Delay(1000);
  LCD_DisplayStringLine(LINE(2), "MATRIX HAS YOU...");

  Delay(2000);

  LCD_DisplayStringLine(LINE(4), "follow" );
  LCD_DisplayStringLine(LINE(5), "the white");
  LCD_DisplayStringLine(LINE(6), "     rabbit");

  Delay(2000);

  LCD_DisplayStringLine(LINE(8), "knock, knock,");
  LCD_DisplayStringLine(LINE(9), "          Neo");

  GPIO_SetBits(GPIOG, GPIO_Pin_13|GPIO_Pin_14);


  while (1)
  {
    GPIO_ToggleBits(GPIOG, GPIO_Pin_13);

    Delay(200);

    GPIO_ToggleBits(GPIOG, GPIO_Pin_14);

    Delay(400);
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

/**
  * @}
  */


/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
