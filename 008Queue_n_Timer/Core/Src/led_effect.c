#include "main.h"

void led_effect_stop(void)
{
	/* Stop the 4 timers that control the led toggling */
	for (int i = 0 ; i < 4 ; i++)
	{
		xTimerStop(handle_led_timer[i], portMAX_DELAY);
	}

}

void led_effect(int selector)
{
	/* Stop the current LED effect */
	led_effect_stop();

	/* Start the timer */
	xTimerStart(handle_led_timer[selector - 1], portMAX_DELAY);
}

void turn_off_all_leds(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

void turn_on_all_leds(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
}

void turn_on_odd_leds(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
}

void turn_on_even_leds(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
}

void LED_control(uint8_t led_on)
{
	turn_off_all_leds();

	switch(led_on)
	{
		case 0x1:
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
			break;
		case 0x2:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
			break;
		case 0x4:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
			break;
		case 0x8:
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
			break;
	}
}

void LED_effect1(void)
{
	static int flag = 1;

	/* Toggle all LEDs at the same time */
	(flag ^= 1) ? turn_off_all_leds() : turn_on_all_leds();
}

void LED_effect2(void)
{
	static int flag = 1;

	/* Toggle even LEDs first and then odd LEDs */
	(flag ^= 1) ? turn_on_even_leds() : turn_on_odd_leds();
}

void LED_effect3(void)
{
	static int i = 0;

	/* Turn on the LEDs following a left shift sequence */
	LED_control( 0x1 << (i++ % 4) );
}

void LED_effect4(void)
{
	static int i = 0;

	/* Turn on the LEDs following a right shift sequence */
	LED_control( 0x8 >> (i++ % 4) );
}
