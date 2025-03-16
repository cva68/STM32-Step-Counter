/*
 * app.c
 *
 * Round-robbin scheduler for the blinking LED, button tasks, joystick updates, display updates and UART debug info.
 * Scheduling code based on that provided on the ENCE260 Learn Page.
 *
 *  Created on: Mar 6, 2025
 *      Author: cva68
 */

#include "app.h"
#include "gpio.h"
#include "task_blinky.h"
#include "task_buttons.h"
#include "task_joystick.h"
#include "task_display.h"
#include "task_uart.h"

#define TICK_FREQUENCY_HZ 1000
#define HZ_TO_TICKS(FREQUENCY_HZ) (TICK_FREQUENCY_HZ/FREQUENCY_HZ)

#define BUTTON_TASK_FREQUENCY 100
#define BLINKY_TASK_FREQUENCY 2
#define JOYSTICK_TASK_FREQUENCY 2
#define DISPLAY_TASK_FREQUENCY 4
#define UART_TASK_FREQUENCY 4

#define BUTTON_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BUTTON_TASK_FREQUENCY)
#define BLINKY_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BLINKY_TASK_FREQUENCY)
#define JOYSTICK_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/JOYSTICK_TASK_FREQUENCY)
#define DISPLAY_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/DISPLAY_TASK_FREQUENCY)
#define UART_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/UART_TASK_FREQUENCY)

static uint32_t buttonTaskNextRun = 0;
static uint32_t blinkyTaskNextRun = 0;
static uint32_t joystickTaskNextRun = 0;
static uint32_t displayTaskNextRun = 0;
static uint32_t uartTaskNextRun = 0;
static bool SW2_state = 0; // This needs to be passed between button and UART layers.


void app_main(void)
{
	// Initialise and start timer.
	uint32_t ticks;
	buttonTaskNextRun = HAL_GetTick() + BUTTON_TASK_PERIOD_TICKS;
	blinkyTaskNextRun = HAL_GetTick() + BLINKY_TASK_PERIOD_TICKS;
	joystickTaskNextRun = HAL_GetTick() + JOYSTICK_TASK_PERIOD_TICKS;
	displayTaskNextRun = HAL_GetTick() + DISPLAY_TASK_PERIOD_TICKS;

	// Initialise tasks.
	buttons_task_init();
	display_task_init();


	// Periodically execute tasks at the frequency defined above.
	while(1)
	{
		ticks = HAL_GetTick();

		if(ticks > buttonTaskNextRun) {
			SW2_state = buttons_task_execute();
			buttonTaskNextRun += BUTTON_TASK_PERIOD_TICKS;
		}

		if (ticks > blinkyTaskNextRun) {
			blinky_task_execute();
			blinkyTaskNextRun += BLINKY_TASK_PERIOD_TICKS;
		}

		if (ticks > joystickTaskNextRun) {
			joystick_task_execute();
			joystickTaskNextRun += JOYSTICK_TASK_PERIOD_TICKS;
		}

		if (ticks > displayTaskNextRun) {
			display_task_execute();
			displayTaskNextRun += DISPLAY_TASK_PERIOD_TICKS;
		}

		if (ticks > uartTaskNextRun) {
			uart_task_execute(SW2_state);
			uartTaskNextRun += UART_TASK_PERIOD_TICKS;
		}
	}
}



