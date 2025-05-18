/*
 * task_led.c
 *
 * Task to turn on LEDs as the step goal approaches completion. DS4 lights up gradually
 * with PWM from 0% to 25% completion, DS1-DS3 turn on for the remaining 25% increments.
 *
 *  Created on: May 12, 2025
 *      Authors: C. Varney, A. Walker
 */

#include <stdint.h>
#include "task_led.h"
#include "gpio.h"
#include "pwm.h"
#include "steps.h"

uint16_t current_count;
uint16_t completion;
uint16_t current_goal;
uint16_t duty_cycle;

void task_led_initTask(void) {
	// Enable GPIO outputs, with PWM on DS4
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET );
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET );
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET );
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
}

void task_led_executeTask(void) {
	current_count = steps_getStepCount();
	current_goal = steps_getStepGoal();
	completion = steps_getGoalPercentage();

	if (completion <= 25) {
	    duty_cycle = (current_count * 100) / current_goal * 4; // scale 0–25% to 0–100
	} else {
	    duty_cycle = 100; // clamp at 100%
	}

	if (completion >= 50) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET );
	} else {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET );
	}

	if (completion >= 75) {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET );
	} else {
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET );
	}

	if (completion >= 100) {
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_RESET );
	} else {
		HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3, GPIO_PIN_SET );
	}
	pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, duty_cycle);
} // task_led_executeTask
