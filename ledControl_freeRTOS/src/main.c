

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "FreeRTOS.h"
#include "task.h"

TaskHandle_t myButtonTaskHandle = NULL;
TaskHandle_t myLedTaskHandle = NULL;

void readButtonStateTask(void *params);
void ledFlashTask(void *params);

int main(void)
{

	RCC_DeInit();		//	hseoff | hsi on | plloff

	SystemCoreClockUpdate();	// 	systemclock update to 16mhx

	xTaskCreate(readButtonStateTask,
				"Buton Okuma Görevi",
				configMINIMAL_STACK_SIZE,
				NULL,
				3,
				&myButtonTaskHandle);

	xTaskCreate(ledFlashTask,
				"Led Kontrol Görevi",
				configMINIMAL_STACK_SIZE,
				NULL,
				3,
				&myLedTaskHandle);

	vTaskStartScheduler();

  /* Infinite loop */
  while (1)
  {

  }
}

void readButtonStateTask(void *params)
{
	while(1)
	{

	}
}

void ledFlashTask(void *params)
{
	while(1)
	{

	}
}

/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
