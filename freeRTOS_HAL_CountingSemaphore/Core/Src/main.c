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
#include "semphr.h"
#include "string.h"
#include "stdlib.h"
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
char myMessages[100];


void Handler_Task_Handler(void *parameters);
void Periodic_Task_Handler(void *parameters);
void sendMessage(char *message);
void softwareInterruptConfig(void);
void softwareInterrupt(void);

/*************************tasks***********************************************/
TaskHandle_t task1Handler 		= NULL;
TaskHandle_t task2Periodic 		= NULL;

/*************************semaphore*******************************************/
SemaphoreHandle_t xCountingSemaphore = NULL;

void sendMessage(char *message)
{
	while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TXE) != SET);
	HAL_UART_Transmit (&huart2, &message[0], strlen(message), portMAX_DELAY);
}


void Periodic_Task_Handler(void *parameters)
{
	while(1)
	{
		sendMessage("periodicTask: Pending the interrupt. \r\n");
		vTaskDelay(pdMS_TO_TICKS(500));

		HAL_NVIC_SetPendingIRQ(EXTI0_IRQn);
		sendMessage("periodicTask: Resuming. \r\n");
	}
}
void Handler_Task_Handler(void *parameters)
{
	while(1)
	{
		xSemaphoreTake(xCountingSemaphore, portMAX_DELAY);

		sendMessage("Handler task: processing events. \r\n");
	}
}
void softwareInterruptConfig(void)
{
	HAL_NVIC_SetPriority(EXTI0_IRQn, configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY, 0);
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

}

void softwareInterrupt(void)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

	sendMessage("interrupt active. \r\n");

	xSemaphoreGiveFromISR(xCountingSemaphore, &xHigherPriorityTaskWoken);		// 1 count semaphore
	xSemaphoreGiveFromISR(xCountingSemaphore, &xHigherPriorityTaskWoken);		// 2 count semaphore
	xSemaphoreGiveFromISR(xCountingSemaphore, &xHigherPriorityTaskWoken);		// 3 count semaphore
	xSemaphoreGiveFromISR(xCountingSemaphore, &xHigherPriorityTaskWoken);		// 4 count semaphore
	xSemaphoreGiveFromISR(xCountingSemaphore, &xHigherPriorityTaskWoken);		// 5 count semaphore
	xSemaphoreGiveFromISR(xCountingSemaphore, &xHigherPriorityTaskWoken);		// 6 count semaphore
	xSemaphoreGiveFromISR(xCountingSemaphore, &xHigherPriorityTaskWoken);		// 7 count semaphore
	xSemaphoreGiveFromISR(xCountingSemaphore, &xHigherPriorityTaskWoken);		// 8 count semaphore
	xSemaphoreGiveFromISR(xCountingSemaphore, &xHigherPriorityTaskWoken);		// 9 count semaphore
	xSemaphoreGiveFromISR(xCountingSemaphore, &xHigherPriorityTaskWoken);		// 10 count semaphore

	portEND_SWITCHING_ISR(xHigherPriorityTaskWoken);
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

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
  /* USER CODE BEGIN 2 */

  sendMessage("Counting Semaphore Usage Interrupt and task\r\n");

  xCountingSemaphore = xSemaphoreCreateCounting(10, 0);

  if((xCountingSemaphore != NULL))
  {

	  sendMessage("Semaphore and Tasks are created\r\n");
	  softwareInterruptConfig();
	  xTaskCreate(Handler_Task_Handler,
				  "Handler Task",
				  configMINIMAL_STACK_SIZE*3,
				  NULL,
				  1,
				  &task1Handler);

	  xTaskCreate(Periodic_Task_Handler,
				  "Periodic Task",
				  configMINIMAL_STACK_SIZE*3,
				  NULL,
				  3,
				  &task2Periodic);

	  vTaskStartScheduler();
  }
  else
  {
	  sendMessage("Semaphore and Tasks are not created\r\n");

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

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

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
