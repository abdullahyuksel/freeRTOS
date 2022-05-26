/* Includes */
#include "stm32f4xx.h"

#include "FreeRTOS.h"
#include "task.h"


TaskHandle_t TASK1_Handle = NULL;
TaskHandle_t TASK2_Handle = NULL;

void Task1_Handler(void *params);
void Task2_Handler(void *params);

int main(void) {

	// 1. Adým sistem saati dahili saat olarak tanýmlandý
	RCC_DeInit();  					// HSI ON | HSE OFF | PLL OFF | SystemClock 16MHZ

	// 2. adým sistem saati yeni ayarlara göre güncellendi
	SystemCoreClockUpdate();		// system CoreClock Update

	// 3. Adým Görev Olusturma
	xTaskCreate(Task1_Handler,
				"Task 1",
				configMINIMAL_STACK_SIZE,
				NULL,
				4,
				&TASK1_Handle);

	xTaskCreate(Task2_Handler,
				"Task 2",
				configMINIMAL_STACK_SIZE,
				NULL,
				4,
				&TASK2_Handle);

	vTaskStartScheduler();
	/* Infinite loop */
	while (1) {

	}
}

void Task1_Handler(void *params)
{
	while(1)
	{

	}
}

void Task2_Handler(void *params)
{
	while(1)
	{

	}
}
