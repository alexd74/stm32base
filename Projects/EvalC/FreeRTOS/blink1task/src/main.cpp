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
void Task1( void *pvParameters )
{
	while( 1 ){
		static bool State;
		switch( State ){
			case false: GPIO_SetBits( GPIOD, GPIO_Pin_4 );
						vTaskDelay( 100 / portTICK_RATE_MS );
						State = true;
						break;

			case true:	GPIO_ResetBits( GPIOD, GPIO_Pin_4 );
						vTaskDelay( 100 / portTICK_RATE_MS );
						State = false;
						break;
		}
	}
}
//---------------------------------------------------------------------------

int main()
{
	// switch clock to GPIOD
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE );

 	GPIO_InitTypeDef  GPIO_InitStructure;
	
	// Configure PE4, LED0
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init( GPIOD, &GPIO_InitStructure );
	
	xTaskCreate( Task1,(signed char *)"TSK", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	
 	/* Start the scheduler. */
	vTaskStartScheduler();

	return 0;
}
//---------------------------------------------------------------------------
