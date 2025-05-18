/*
 * app.c
 *
 * Time-based scheduler for each step counter task, implementing an interrupt-driven kernel
 * with HAL_GetTick().
 * 
 * Modified from code provided by the University of Canterbury (ENCE361)
 *
 *  Created on: Mar 6, 2025
 *  	Authors: Connor Varney, Auron Walker
 */

#include <stdint.h>

#include "app.h"
#include "task_adc.h"
#include "gpio.h"
#include "task_buttons.h"
#include "task_joystick.h"
#include "task_fsm.h"
#include "task_buzzer.h"
#include "task_imu.h"
#include "task_led.h"

// Define systick frequency, and conversion rate from HZ to Ticks
#define TICK_FREQUENCY_HZ 1000
#define HZ_TO_TICKS(FREQUENCY_HZ) (TICK_FREQUENCY_HZ/FREQUENCY_HZ)

// Task frequencies
#define BUTTON_TASK_FREQUENCY 100
#define JOYSTICK_TASK_FREQUENCY 10
#define DISPLAY_FSM_TASK_FREQUENCY 6
#define ADC_TASK_FREQUENCY 10
#define BUZZER_TASK_FREQUENCY 6
#define IMU_TASK_FREQUENCY 50
#define LED_TASK_FREQUENCY 6

// Conversion of task frequencies to ticks
#define BUTTON_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BUTTON_TASK_FREQUENCY)
#define JOYSTICK_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/JOYSTICK_TASK_FREQUENCY)
#define DISPLAY_FSM_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/DISPLAY_FSM_TASK_FREQUENCY)
#define ADC_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/ADC_TASK_FREQUENCY)
#define BUZZER_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BUZZER_TASK_FREQUENCY)
#define IMU_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/IMU_TASK_FREQUENCY)
#define LED_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/LED_TASK_FREQUENCY)

// Delay some tasks until ADC transients have dissipated
#define ADC_TASK_OFFSET 50

// Static variables to store next run time of each task
static uint32_t buttonTaskNextRun = 0;
static uint32_t joystickTaskNextRun = 0;
static uint32_t displayFSMTaskNextRun = 0;
static uint32_t adcTaskNextRun = 0;
static uint32_t buzzerTaskNextRun = 0;
static uint32_t imuTaskNextRun = 0;
static uint32_t ledTaskNextRun = 0;

void app_main(void)
{
	// Initialise and start timer.
	uint32_t ticks;
	buttonTaskNextRun = HAL_GetTick() + BUTTON_TASK_PERIOD_TICKS;
	joystickTaskNextRun = HAL_GetTick() + JOYSTICK_TASK_PERIOD_TICKS + ADC_TASK_OFFSET;
	displayFSMTaskNextRun = HAL_GetTick() + DISPLAY_FSM_TASK_PERIOD_TICKS + ADC_TASK_OFFSET;
	adcTaskNextRun = HAL_GetTick() + ADC_TASK_PERIOD_TICKS;
	buzzerTaskNextRun = HAL_GetTick() + BUZZER_TASK_PERIOD_TICKS;
	imuTaskNextRun = HAL_GetTick() + IMU_TASK_PERIOD_TICKS;
	ledTaskNextRun = HAL_GetTick() + LED_TASK_PERIOD_TICKS;

	// Initialise tasks.
	task_buttons_initTask();
	task_fsm_initTask();
	task_buttons_initTask();
	task_imu_initTask();
	task_led_initTask();

	// Periodically execute tasks at the frequency defined above.
	while(1)
	{
		ticks = HAL_GetTick();

		if(ticks > buttonTaskNextRun) {
			task_buttons_executeTask();
			buttonTaskNextRun += BUTTON_TASK_PERIOD_TICKS;
		}

		if (ticks > joystickTaskNextRun) {
			task_joystick_executeTask();
			joystickTaskNextRun += JOYSTICK_TASK_PERIOD_TICKS;
		}

		if (ticks > displayFSMTaskNextRun) {
			task_fsm_taskExecute();
			displayFSMTaskNextRun += DISPLAY_FSM_TASK_PERIOD_TICKS;
		}

		if (ticks > adcTaskNextRun) {
			task_adc_executeTask();
			adcTaskNextRun += ADC_TASK_PERIOD_TICKS;
		}

		if (ticks > buzzerTaskNextRun) {
			task_buzzer_executeTask();
			buzzerTaskNextRun += BUZZER_TASK_PERIOD_TICKS;
		}

		if (ticks > imuTaskNextRun){
			task_imu_executeTask();
			imuTaskNextRun += IMU_TASK_PERIOD_TICKS;
		}

		if (ticks > ledTaskNextRun){
			task_led_executeTask();
			ledTaskNextRun += LED_TASK_PERIOD_TICKS;
		}
	}
}  // app_main
