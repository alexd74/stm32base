#include "stm32f4xx.h"
//---------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
//---------------------------------------------------------------------------
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
//---------------------------------------------------------------------------
void vTaskLED1(void *pvParameters)
{
	for (;;)
  {
    GPIO_SetBits( GPIOG, GPIO_Pin_13 );
		vTaskDelay(500);
    GPIO_ResetBits( GPIOG, GPIO_Pin_13 );
		vTaskDelay(500);
	}

}

void vTaskLED2(void *pvParameters)
{
	for (;;)
  {
    GPIO_SetBits( GPIOG, GPIO_Pin_14 );
		vTaskDelay(321);
    GPIO_ResetBits( GPIOG, GPIO_Pin_14 );
		vTaskDelay(321);
	}

}
//---------------------------------------------------------------------------

int main()
{
  /* GPIOG Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

  GPIO_InitTypeDef  GPIO_InitStructure;
  /* Configure PD13 and PD14 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13| GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

	xTaskCreate( vTaskLED1, ( signed char * ) "LED1", configMINIMAL_STACK_SIZE, NULL, 2,
			( xTaskHandle * ) NULL);
	xTaskCreate( vTaskLED2, ( signed char * ) "LED2", configMINIMAL_STACK_SIZE, NULL, 2,
			( xTaskHandle * ) NULL);

  /* Start the scheduler. */
  vTaskStartScheduler();

	/* Will only get here if there was insufficient memory to create the idle
	 task.  The idle task is created within vTaskStartScheduler(). */
	for (;;)
		;

	return 0;
}
//---------------------------------------------------------------------------
