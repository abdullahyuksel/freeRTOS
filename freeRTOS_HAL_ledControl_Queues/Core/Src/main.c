/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
 UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

 /*************************definations*****************************************/

#define LED_ON 			1
#define LED_OFF			2
#define LED_TOGGLE_ON	3
#define LED_TOGGLE_OFF	4
#define LED_STATUS		5
#define LED_EXIT		6

 typedef struct
 {
	 uint8_t COMMAND_NUM;
	 uint8_t COMMAND_ARGS[10];
 }AppCommands_t;

 char menu[]={	 "    				 \r\n" \
		 	 	 "Menu************** \r\n" \
		 	 	 "Led On		-> 1 \r\n" \
		 	 	 "Led Off		-> 2 \r\n" \
				 "Led Toggle On	-> 3 \r\n" \
				 "Led Toggle Off-> 4 \r\n" \
				 "Led Status	-> 5 \r\n" \
				 "Led App Exit	-> 6 \r\n" \
				 "    				 \r\n" \
				 "Type Your Option:  \r\n" };

 /*************************tasks***********************************************/
 TaskHandle_t task1MenuHandle 			= NULL;
 TaskHandle_t task2CommandHandle 		= NULL;
 TaskHandle_t task3CommandProcessHandle = NULL;
 TaskHandle_t task4UartWriteHandle 		= NULL;

 /***********************queues***********************************************/
 QueueHandle_t UartWriteQueue 	= NULL;
 QueueHandle_t CommandQueue 	= NULL;

 /***********************timers***********************************************/
 TimerHandle_t LedTimerHandle 	= NULL;

 /***********************variables********************************************/
uint8_t rxData=0;
uint8_t rxDataBuff[20]={0};
uint8_t rxDataCount=0;

/***********************functions*********************************************/
 void Task1_Menu_Display(void *params);
 void Task2_Command_Handling_Handler(void *params);
 void Task3_Command_Process_Handler(void *params);
 void Task4_Uart_Write_Handler(void *params);
 uint8_t getCommandCode(uint8_t *buffer);
 uint8_t getArguments(uint8_t *buffer);

 void ledOn(void);
 void ledOff(void);
 void ledToggleOff(void);
 void ledToggleOn(uint32_t duration);
 void ledStatus(char *ledStateMessage);
 void ledExit(char *ledExitMessage);
 void ledError(char *ledErrorMessage);

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */

uint8_t getCommandCode(uint8_t *buffer)
{
	return buffer[0]-48;
}
uint8_t getArguments(uint8_t *buffer)
{
	return buffer[0];
}
void ledOn(void)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_SET);
}
void ledOff(void)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);
}
void toggle(void)
{
	HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15);
}
void ledToggleOn(uint32_t duration)
{
	if(LedTimerHandle == NULL)
		LedTimerHandle = xTimerCreate("LedToggleTimer", duration, 1, 0, toggle);

	xTimerStart(LedTimerHandle, portMAX_DELAY);
}
void ledToggleOff(void)
{
	xTimerStop(LedTimerHandle, portMAX_DELAY);
	ledOff();
}
void ledExit(char *ledExitMessage)
{
	sprintf(ledExitMessage, "System is closing and go to sleep \r\n");
	xQueueSend(UartWriteQueue, &ledExitMessage, portMAX_DELAY);

	vTaskDelete(task1MenuHandle);
	vTaskDelete(task2CommandHandle);
	vTaskDelete(task3CommandProcessHandle);
	vTaskDelete(task4UartWriteHandle);

	HAL_UART_DeInit(&huart2);

	HAL_NVIC_DisableIRQ(USART2_IRQn);
}
void ledError(char *ledErrorMessage)
{
	sprintf(ledErrorMessage, "Wrong Led Status \r\n");
	xQueueSend(UartWriteQueue, &ledErrorMessage, portMAX_DELAY);
}
void ledStatus(char *ledStateMessage)
{
	sprintf(ledStateMessage, "Led Status is: %d \r\n", HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12));
	xQueueSend(UartWriteQueue, &ledStateMessage, portMAX_DELAY);
}
void vApplicationIdleHook(void)
{
//	HAL_PWR_EnterSTANDBYMode
	 __WFI();
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	if(huart->Instance == USART2 )
	{

		if(rxData == 10)
		{
			xTaskNotifyFromISR(task1MenuHandle, 0, eNoAction, xHigherPriorityTaskWoken);
			xTaskNotifyFromISR(task2CommandHandle, 0, eNoAction, xHigherPriorityTaskWoken);
			rxDataCount=0;
		}
		else
			rxDataBuff[rxDataCount++]=rxData;


		__HAL_UART_CLEAR_FLAG(&huart2,UART_FLAG_RXNE);
		HAL_UART_Receive_IT(&huart2, &rxData, sizeof(rxData));
	}

	if(xHigherPriorityTaskWoken == pdTRUE)
	{
		taskYIELD();
	}
}

void sendMessage(char *message)
{
	while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TXE) != SET);
	HAL_UART_Transmit (&huart2, &message[0], strlen(message), portMAX_DELAY);
}

void Task1_Menu_Display(void *params)
{
	char *task1RxData = menu;

	while(1)
	{

		//send data -> uart_queue
		xQueueSend(UartWriteQueue, &task1RxData, portMAX_DELAY);
		//wait notify
		xTaskNotifyWait(0, 0, NULL, portMAX_DELAY);
	}
}
void Task2_Command_Handling_Handler(void *params)
{
	uint8_t commandCode=0;

	AppCommands_t *appTxCmd;
	while(1)
	{
		xTaskNotifyWait(0, 0, 0, portMAX_DELAY);
		appTxCmd = (AppCommands_t*)pvPortMalloc(sizeof(AppCommands_t));

		taskENTER_CRITICAL();
		commandCode = getCommandCode(&rxDataBuff[0]);
		appTxCmd->COMMAND_NUM=commandCode;
		getArguments(appTxCmd->COMMAND_ARGS);
		taskEXIT_CRITICAL();
		//command_buffer -> command_queue
		xQueueSend(CommandQueue, &appTxCmd, portMAX_DELAY);
	}
}
void Task3_Command_Process_Handler(void *params)
{
	AppCommands_t *appRxCmd;
	char taskStateMessage[50];
	uint16_t toggleTime = pdMS_TO_TICKS(500);
	while(1)
	{
		//READ FROM COMMAND_QUEUE
		xQueueReceive(CommandQueue, (void*)&appRxCmd, portMAX_DELAY);

		//PROCESS
		if(appRxCmd->COMMAND_NUM == LED_ON)
		{
			ledOn();
		}
		else if(appRxCmd->COMMAND_NUM == LED_OFF)
		{
			ledOff();
		}
		else if(appRxCmd->COMMAND_NUM == LED_TOGGLE_ON)
		{
			ledToggleOn(toggleTime);
		}
		else if(appRxCmd->COMMAND_NUM == LED_TOGGLE_OFF)
		{
			ledToggleOff();
		}
		else if(appRxCmd->COMMAND_NUM == LED_STATUS)
		{
			ledStatus(taskStateMessage);
		}
		else if(appRxCmd->COMMAND_NUM == LED_EXIT)
		{
			ledExit(taskStateMessage);
		}
		else
			ledError(taskStateMessage);
	}
}
void Task4_Uart_Write_Handler(void *params)
{
	char *task4TxData=NULL;
	while(1)
	{
		//READ FROM UART_WRITE_QUEUE
		xQueueReceive(UartWriteQueue, &task4TxData, portMAX_DELAY);
		//SEND MESSAGE
		sendMessage(task4TxData);
	}
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */



  sendMessage("This is Queue Command processing.\r\n");

  UartWriteQueue 	= xQueueCreate(50, sizeof(char *));
  CommandQueue		= xQueueCreate(10, sizeof(AppCommands_t));

  if((UartWriteQueue != NULL) && (CommandQueue != NULL))
  {


	  sendMessage("Queue creation succesful.\r\n");

	  xTaskCreate(Task1_Menu_Display,
				  "task1 Menu Display",
				  configMINIMAL_STACK_SIZE*3,
				  NULL,
				  1,
				  &task1MenuHandle);

	  xTaskCreate(Task2_Command_Handling_Handler,
				  "task2 Command Handling",
				  configMINIMAL_STACK_SIZE*3,
				  NULL,
				  2,
				  &task2CommandHandle);

	  xTaskCreate(Task3_Command_Process_Handler,
				  "task3 Command Process",
				  configMINIMAL_STACK_SIZE*3,
				  NULL,
				  2,
				  &task3CommandProcessHandle);

	  xTaskCreate(Task4_Uart_Write_Handler,
				  "task4 Uart Write",
				  configMINIMAL_STACK_SIZE*3,
				  NULL,
				  2,
				  &task4UartWriteHandle);

	  vTaskStartScheduler();
  }
  else
  {

	  sendMessage("Queue creation failed.\r\n");
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* USART2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART2_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY, 0);
  HAL_NVIC_EnableIRQ(USART2_IRQn);
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */
  HAL_UART_Receive_IT(&huart2, &rxData, sizeof(rxData));
  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM6) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
