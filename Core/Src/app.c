#include "app.h"
#include "gpio.h"
#include "rgb.h"
#include "buttons.h"

#define TICK_FREQUENCY_HZ 1000
#define HZ_TO_TICKS(FREQUENCY_HZ) (TICK_FREQUENCY_HZ/FREQUENCY_HZ)

#define BUTTON_TASK_FREQUENCY 100
#define BLINKY_TASK_FREQUENCY 2

#define BUTTON_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BUTTON_TASK_FREQUENCY)
#define BLINKY_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BLINKY_TASK_FREQUENCY)

static uint32_t buttonTaskNextRun = 0;
static uint32_t blinkyTaskNextRun = 0;

void button_task_execute(void);
void blinky_task_execute(void);

void app_main(void)
{
	// Initialize and start timer

	buttons_init();

	buttonTaskNextRun = HAL_GetTick() + BUTTON_TASK_PERIOD_TICKS;
	blinkyTaskNextRun = HAL_GetTick() + BLINKY_TASK_PERIOD_TICKS;
	uint32_t ticks = HAL_GetTick();

	while(1)
	{
		rgb_colour_on(RGB_RED);
		rgb_colour_on(RGB_GREEN);
		rgb_colour_on(RGB_BLUE);
		ticks = HAL_GetTick();

		if(ticks > buttonTaskNextRun)
		{
		  button_task_execute();
		  buttonTaskNextRun += BUTTON_TASK_PERIOD_TICKS;
		}

		if (ticks > blinkyTaskNextRun)
		{
		  blinky_task_execute();
		  blinkyTaskNextRun += BLINKY_TASK_PERIOD_TICKS;
		}
	}
}

void button_task_execute(void) {
	// Update the buttons
	buttons_update();


	if (buttons_checkButton(UP) == PUSHED) {
		rgb_led_toggle(RGB_UP);
	}

	if (buttons_checkButton(DOWN) == PUSHED) {
		rgb_led_toggle(RGB_DOWN);
	}

	if (buttons_checkButton(LEFT) == PUSHED) {
		rgb_led_toggle(RGB_LEFT);
	}

	if (buttons_checkButton(RIGHT) == PUSHED) {
		rgb_led_toggle(RGB_RIGHT);
	}
}

void blinky_task_execute(void) {
	// Toggle LD1
	HAL_GPIO_TogglePin(NUCLEO_LD1_GPIO_Port, NUCLEO_LD1_Pin);
}
