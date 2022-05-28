

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "FreeRTOS.h"
#include "task.h"
typedef enum
{
	ms_100,
	ms_250,
	ms_500,
	ms_750,
	ms_1000
}msecTime;

typedef struct
{
	msecTime count;
}ledConf_t;

TaskHandle_t myButtonTaskHandle = NULL;
TaskHandle_t myLedTaskHandle = NULL;

void setupConfig(void);
void gpioConfig(void);

void readButtonStateTask(void *params);
void ledFlashTask(void *params);

ledConf_t ledConf;

int main(void)
{

	RCC_DeInit();		//	hseoff | hsi on | plloff

	SystemCoreClockUpdate();	// 	systemclock update to 16mhx

	setupConfig();

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
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	==	Bit_SET)
		{
			while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)	==	Bit_SET){

			}


			if(ledConf.count > ms_1000) ledConf.count = ms_100;
			else ledConf.count++;

		}
	}
}

void ledFlashTask(void *params)
{

	while(1)
	{
		switch (ledConf.count)
		{
			case ms_100:
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				vTaskDelay(100);
			}
			case ms_250:
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				vTaskDelay(250);
			}
			case ms_500:
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				vTaskDelay(500);
			}
			case ms_750:
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				vTaskDelay(750);
			}
			case ms_1000:
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				vTaskDelay(1000);
			}
			default:
			{
				GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
			}
		}

	}
}

void setupConfig(void)
{
	gpioConfig();
}
void gpioConfig(void)
{
	//button configuration
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GpioInitStruct_B = {0};

	GpioInitStruct_B.GPIO_Mode 	=	GPIO_Mode_IN;
	GpioInitStruct_B.GPIO_OType 	=	GPIO_OType_PP;
	GpioInitStruct_B.GPIO_Pin		=	GPIO_Pin_0;
	GpioInitStruct_B.GPIO_PuPd	=	GPIO_PuPd_NOPULL;
	GpioInitStruct_B.GPIO_Speed	=	GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GpioInitStruct_B);

	//leds configuration
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GpioInitStruct_L = {0};

	GpioInitStruct_L.GPIO_Mode 	=	GPIO_Mode_OUT;
	GpioInitStruct_L.GPIO_OType 	=	GPIO_OType_PP;
	GpioInitStruct_L.GPIO_Pin		=	GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GpioInitStruct_L.GPIO_PuPd	=	GPIO_PuPd_NOPULL;
	GpioInitStruct_L.GPIO_Speed	=	GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GpioInitStruct_L);

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
