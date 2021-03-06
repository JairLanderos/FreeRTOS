#include "main.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_RTC_Init(void);
static void MX_USART2_UART_Init(void);
void led_effect_callback(TimerHandle_t xTimer);

RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart2;

TaskHandle_t handle_menu_task;
TaskHandle_t handle_led_task;
TaskHandle_t handle_rtc_task;
TaskHandle_t handle_print_task;
TaskHandle_t handle_command_task;

QueueHandle_t q_data;
QueueHandle_t q_print;

TimerHandle_t handle_led_timer[4];

volatile uint8_t user_data;

state_t current_state = sMainMenu;

int main(void)
{
	BaseType_t status;

	HAL_Init();

	SystemClock_Config();

	MX_GPIO_Init();
	MX_RTC_Init();
	MX_USART2_UART_Init();

	/* Task 1 creation (Menu) */
	status = xTaskCreate(menu_task, "menu_task", 250, NULL, 2, &handle_menu_task);
	configASSERT(status == pdPASS);

	/* Task 2 creation  (LED) */
	status = xTaskCreate(led_task, "led_task", 250, NULL, 2, &handle_led_task);
	configASSERT(status == pdPASS);

	/* Task 3 creation (RTC) */
	status = xTaskCreate(rtc_task, "rtc_task", 250, NULL, 2, &handle_rtc_task);
	configASSERT(status == pdPASS);

	/* Task 4 creation (Print) */
	status = xTaskCreate(print_task, "print_task", 250, NULL, 2, &handle_print_task);
	configASSERT(status == pdPASS);

	/* Task 5 creation (Command handling) */
	status = xTaskCreate(command_task, "command_task", 250, NULL, 2, &handle_command_task);
	configASSERT(status == pdPASS);

	/* Queue 1 creation (receive command) */
	q_data =  xQueueCreate(10, sizeof(char));
	configASSERT(q_data != NULL);

	/* Queue 2 creation (print message) */
	q_print = xQueueCreate(10, sizeof(size_t));
	configASSERT(q_print != NULL);

	/* Create software timers for LED effects */
	for (int i = 0 ; i < 4 ; i++)
	{
		handle_led_timer[i] = xTimerCreate("led_timer",
											pdMS_TO_TICKS(500),
											pdTRUE,
											(void*)(i+1),
											led_effect_callback);
	}

	HAL_UART_Receive_IT(&huart2, (uint8_t*)&user_data, 1);

	/* Start the scheduler */
	vTaskStartScheduler();


	while (1)
	{

	}

}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */
  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_12;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  /* USER CODE END RTC_Init 2 */

}

static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
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

static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* Configure external LED pins */
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_4;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_0;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

void led_effect_callback(TimerHandle_t xTimer)
{
	int id;

	id = (uint32_t)pvTimerGetTimerID(xTimer);

	switch(id)
	{
	case 1:
		LED_effect1();
		break;
	case 2:
		LED_effect2();
		break;
	case 3:
		LED_effect3();
		break;
	case 4:
		LED_effect4();
		break;
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t dummy_reception;

	if(xQueueIsQueueFullFromISR(q_data) == pdFALSE)
	{
		/*Queue is not full */
		xQueueSendFromISR(q_data, (void*)&user_data, NULL);
	}else{
		/*Queue is full */
		if(user_data == '\n')
		{
			/*user_data = '\n' */
			xQueueReceiveFromISR(q_data, (void*)&dummy_reception, NULL);
			xQueueSendFromISR(q_data, (void*)&user_data, NULL);
		}
	}

	/* Send notification to command handling task if user_data = '\n' */
	if (user_data == '\n')
	{
		xTaskNotifyFromISR(handle_command_task, 0, eNoAction, NULL);
	}

	/* Enable UART data byte reception again in IT mode */
	HAL_UART_Receive_IT(&huart2, (uint8_t*)&user_data, 1);


}

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

