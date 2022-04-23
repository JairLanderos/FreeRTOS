#include "main.h"
#include "FreeRTOS.h"
#include "task.h"

#define DWT_CTRL    (*(volatile uint32_t*)0xE0001000)

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void led1_handler(void* parameters);
static void led2_handler(void* parameters);
static void led3_handler(void* parameters);
static void button_handler(void* parameters);

TaskHandle_t led1_handle;
TaskHandle_t led2_handle;
TaskHandle_t led3_handle;
TaskHandle_t btn_handle;

TaskHandle_t volatile next_task_handle = NULL;

int main(void)
{
	BaseType_t status;

	HAL_Init();

	SystemClock_Config();

	MX_GPIO_Init();

	/* Enable the CYCCNT counter */
	DWT_CTRL |= ( 1 << 0);

	/* Task 1 creation (LED 1) */
	status = xTaskCreate(led1_handler, "LED1_task", 200, NULL, 3, &led1_handle);
	configASSERT(status == pdPASS);

	next_task_handle = led1_handle;

	/* Task 2 creation (LED 2) */
	status = xTaskCreate(led2_handler, "LED2_task", 200, NULL, 2, &led2_handle);
	configASSERT(status == pdPASS);

	/* Task 3 creation (LED 3) */
	status = xTaskCreate(led3_handler, "LED3_task", 200, NULL, 1, &led3_handle);
	configASSERT(status == pdPASS);

	/* Task 4 creation (Button) */
	status = xTaskCreate(button_handler, "Button_task", 200, NULL, 4, &btn_handle);
	configASSERT(status == pdPASS);

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
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

  /*Configure GPIO pins : USART_TX_Pin USART_RX_Pin */
  GPIO_InitStruct.Pin = USART_TX_Pin|USART_RX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* Configure LED tasks GPIO pins */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_1;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_4;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

static void led1_handler(void *parameters)
{
	BaseType_t status;

	while(1)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_0);
		status = xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(1000));
		if (status == pdTRUE)
		{
			vTaskSuspendAll();
			next_task_handle = led2_handle;
			xTaskResumeAll();
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
			vTaskDelete(NULL);
		}
	}
}

static void led2_handler(void *parameters)
{
	BaseType_t status;

	while(1)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
		status = xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(800));
		if (status == pdTRUE)
		{
			vTaskSuspendAll();
			next_task_handle = led3_handle;
			xTaskResumeAll();
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
			vTaskDelete(NULL);
		}
	}
}

static void led3_handler(void *parameters)
{
	BaseType_t status;

	while(1)
	{
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
		status = xTaskNotifyWait(0, 0, NULL, pdMS_TO_TICKS(400));
		if (status == pdTRUE)
		{
			vTaskSuspendAll();
			next_task_handle = NULL;
			xTaskResumeAll();
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
			vTaskDelete(btn_handle);
			vTaskDelete(NULL);
		}
	}
}

static void button_handler(void *parameters)
{
	uint8_t button_read = 1;
	uint8_t prev_read = 1;

	while(1)
	{
		button_read = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);
		if (!button_read)
		{
			if (prev_read)
				xTaskNotify(next_task_handle, 0, eNoAction);
		}
		prev_read = button_read;
		vTaskDelay(pdMS_TO_TICKS(10));
	}
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

