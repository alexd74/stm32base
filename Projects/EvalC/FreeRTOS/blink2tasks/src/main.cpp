#include "stm32f10x_conf.h"
#include "stm32f10x.h"
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
		GPIO_SetBits(GPIOD, GPIO_Pin_3);
		vTaskDelay(500);
		GPIO_ResetBits(GPIOD, GPIO_Pin_3);
		vTaskDelay(500);
	}

}

void vTaskLED2(void *pvParameters)
{
	for (;;)
  {
		GPIO_SetBits(GPIOD, GPIO_Pin_4);
		vTaskDelay(321);
		GPIO_ResetBits(GPIOD, GPIO_Pin_4);
		vTaskDelay(321);
	}

}
//---------------------------------------------------------------------------

int main()
{
	// switch clock to GPIOD
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE );

  GPIO_InitTypeDef  GPIO_InitStructure;

	/**
	 *  LED1 -> PC3 , LED2 -> PC4
	 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3 | GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init( GPIOD, &GPIO_InitStructure );

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
