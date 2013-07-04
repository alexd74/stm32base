/* Standard includes. */
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"


//--------------------------------------------------------------

void vTaskLED1(void *pvParameters) {

	for (;;) {
		GPIO_SetBits(GPIOC, GPIO_Pin_9);
		vTaskDelay(500);
		GPIO_ResetBits(GPIOC, GPIO_Pin_9);
		vTaskDelay(500);
	}

}

void vTaskLED2(void *pvParameters) {

	for (;;) {
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
		vTaskDelay(321);
		GPIO_ResetBits(GPIOC, GPIO_Pin_8);
		vTaskDelay(321);
	}

}


//--------------------------------------------------------------
int main(void) {

	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	/**
	 *  LED1 -> PC8 , LED2 -> PC9
	 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

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
}
/*-----------------------------------------------------------*/

void vApplicationTickHook(void) {

//	TimingDelay_Decrement();
}
/*-----------------------------------------------------------*/
