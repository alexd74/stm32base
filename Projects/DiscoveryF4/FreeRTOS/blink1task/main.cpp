#include "stm32f4xx.h"
//---------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
//---------------------------------------------------------------------------
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
//---------------------------------------------------------------------------
void Task1( void *pvParameters )
{
	while( 1 ){
		static bool State;
		switch( State ){
			case false: GPIO_SetBits( GPIOD, GPIO_Pin_12 );
						vTaskDelay( 100 / portTICK_RATE_MS );
						State = true;
						break;

			case true:	GPIO_ResetBits( GPIOD, GPIO_Pin_12 );
						vTaskDelay( 100 / portTICK_RATE_MS );
						State = false;
						break;
		}
	}
}
//---------------------------------------------------------------------------

int main()
{
  /* GPIOD Periph clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_InitTypeDef  GPIO_InitStructure;
  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

	xTaskCreate( Task1,(signed char *)"TSK", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );

  /* Start the scheduler. */
	vTaskStartScheduler();

	return 0;
}
//---------------------------------------------------------------------------
