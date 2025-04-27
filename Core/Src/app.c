/*
 * app.c
 *
 * Round-robbin scheduler for the blinking LED, button tasks, joystick updates, display updates and UART debug info.
 * Scheduling code based on that provided on the ENCE260 Learn Page.
 *
 *  Created on: Mar 6, 2025
 *      Author: cva68
 */

#include <task_adc.h>
#include "app.h"
#include "gpio.h"
#include "task_buttons.h"
#include "task_joystick.h"
#include "task_uart.h"
#include "task_display_fsm.h"
#include "task_buzzer.h"
#include "adc_controller.h"

#define TICK_FREQUENCY_HZ 1000
#define HZ_TO_TICKS(FREQUENCY_HZ) (TICK_FREQUENCY_HZ/FREQUENCY_HZ)

#define BUTTON_TASK_FREQUENCY 100
#define JOYSTICK_TASK_FREQUENCY 10
#define UART_TASK_FREQUENCY 4
#define DISPLAY_FSM_TASK_FREQUENCY 6
#define ADC_TASK_FREQUENCY 10
#define BUZZER_TASK_FREQUENCY 6

#define BUTTON_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BUTTON_TASK_FREQUENCY)
#define JOYSTICK_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/JOYSTICK_TASK_FREQUENCY)
#define UART_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/UART_TASK_FREQUENCY)
#define DISPLAY_FSM_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/DISPLAY_FSM_TASK_FREQUENCY)
#define ADC_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/ADC_TASK_FREQUENCY)
#define BUZZER_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BUZZER_TASK_FREQUENCY)

// Delay some tasks until ADC transients have dissipated
#define ADC_TASK_OFFSET 50

static uint32_t buttonTaskNextRun = 0;
static uint32_t joystickTaskNextRun = 0;
static uint32_t uartTaskNextRun = 0;
static uint32_t displayFSMTaskNextRun = 0;
static uint32_t adcTaskNextRun = 0;
static uint32_t buzzerTaskNextRun = 0;

void app_main(void)
{
	// Initialise and start timer.
	uint32_t ticks;
	buttonTaskNextRun = HAL_GetTick() + BUTTON_TASK_PERIOD_TICKS;
	joystickTaskNextRun = HAL_GetTick() + JOYSTICK_TASK_PERIOD_TICKS + ADC_TASK_OFFSET;
	uartTaskNextRun = HAL_GetTick() + UART_TASK_PERIOD_TICKS;
	displayFSMTaskNextRun = HAL_GetTick() + DISPLAY_FSM_TASK_PERIOD_TICKS + ADC_TASK_OFFSET;
	adcTaskNextRun = HAL_GetTick() + ADC_TASK_PERIOD_TICKS;
	buzzerTaskNextRun = HAL_GetTick() + BUZZER_TASK_PERIOD_TICKS;

	// Initialise tasks.
	buttons_task_init();
	display_fsm_task_init();
	buzzer_task_init();

	// Periodically execute tasks at the frequency defined above.
	while(1)
	{
		ticks = HAL_GetTick();

		if(ticks > buttonTaskNextRun) {
			buttons_task_execute();
			buttonTaskNextRun += BUTTON_TASK_PERIOD_TICKS;
		}

		if (ticks > joystickTaskNextRun) {
			joystick_task_execute();
			joystickTaskNextRun += JOYSTICK_TASK_PERIOD_TICKS;
		}

		if (ticks > uartTaskNextRun) {
			uart_task_execute();
			uartTaskNextRun += UART_TASK_PERIOD_TICKS;
		}

		if (ticks > displayFSMTaskNextRun) {
			display_fsm_task_execute();
			displayFSMTaskNextRun += DISPLAY_FSM_TASK_PERIOD_TICKS;
		}

		if (ticks > adcTaskNextRun) {
			adc_task_execute();
			adcTaskNextRun += ADC_TASK_PERIOD_TICKS;
		}

		if (ticks > buzzerTaskNextRun) {
			buzzer_task_execute();
			buzzerTaskNextRun += BUZZER_TASK_PERIOD_TICKS;
		}
	}
}



