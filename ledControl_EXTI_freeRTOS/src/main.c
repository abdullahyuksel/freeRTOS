

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

#include "FreeRTOS.h"
#include "task.h"
typedef enum
{
	ms_0,
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
void EXTIConfig(void);
void NVICConfig(void);

void EXTI0_IRQHandler(void)
{
	//external interrupt flag clear
	EXTI_ClearITPendingBit(EXTI_Line0);

	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_SET)
	{
		buttonHandler();
	}
}

void ledFlashTask(void *params);

void buttonHandler(void);

ledConf_t ledConf;

int main(void)
{

	RCC_DeInit();				//	hseoff | hsi on | plloff

	SystemCoreClockUpdate();	// 	systemclock update to 16mhz

	setupConfig();
	EXTIConfig();
	NVICConfig();

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


void ledFlashTask(void *params)
{

	while(1)
	{
		switch (ledConf.count)
		{
			case ms_0:
			{
				GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				break;
			}
			case ms_100:
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				vTaskDelay(100);
				break;
			}
			case ms_250:
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				vTaskDelay(250);
				break;
			}
			case ms_500:
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				vTaskDelay(500);
				break;
			}
			case ms_750:
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				vTaskDelay(750);
				break;
			}
			case ms_1000:
			{
				GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				vTaskDelay(1000);
				break;
			}
			default:
			{
				GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
				ledConf.count = ms_0;
				break;
			}
		}
	}


}

void setupConfig(void)
{
	gpioConfig();
	EXTIConfig();
	NVICConfig();
}
void gpioConfig(void)
{
	//button configuration
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GpioInitStruct_B = {0};

	GpioInitStruct_B.GPIO_Mode 	=	GPIO_Mode_IN;
	GpioInitStruct_B.GPIO_OType =	GPIO_OType_PP;
	GpioInitStruct_B.GPIO_Pin	=	GPIO_Pin_0;
	GpioInitStruct_B.GPIO_PuPd	=	GPIO_PuPd_NOPULL;
	GpioInitStruct_B.GPIO_Speed	=	GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GpioInitStruct_B);

	//leds configuration
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GpioInitStruct_L = {0};

	GpioInitStruct_L.GPIO_Mode 	=	GPIO_Mode_OUT;
	GpioInitStruct_L.GPIO_OType =	GPIO_OType_PP;
	GpioInitStruct_L.GPIO_Pin	=	GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GpioInitStruct_L.GPIO_PuPd	=	GPIO_PuPd_NOPULL;
	GpioInitStruct_L.GPIO_Speed	=	GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GpioInitStruct_L);


}

void EXTIConfig(void)
{
	//external interrupt
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, GPIO_Pin_0);

	EXTI_InitTypeDef EXTI_InitStruct = {0};

	EXTI_InitStruct.EXTI_Line	=	EXTI_Line0;
	EXTI_InitStruct.EXTI_LineCmd=	ENABLE;
	EXTI_InitStruct.EXTI_Mode	=	EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=	EXTI_Trigger_Rising;

	EXTI_Init(&EXTI_InitStruct);
}

void NVICConfig(void)
{
	NVIC_SetPriority(EXTI0_IRQn, 2);
	NVIC_EnableIRQ(EXTI0_IRQn);
}

void buttonHandler(void)
{
	ledConf.count++;
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
