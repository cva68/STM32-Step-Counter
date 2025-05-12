/*
 * task_led.c
 *
 *  Created on: May 12, 2025
 *      Author: awa158
 */

#include "task_led.h"
#include "gpio.h"
#include "pwm.h"
#include "state_task_count.h"
#include "state_task_goal.h"

uint16_t current_goal;
uint16_t current_count;
uint16_t duty_cycle;
uint16_t completion;

void led_task_init(void) {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET );
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET );
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET );
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
}

void led_task_execute(void) {
	current_goal = get_step_goal();
	current_count = get_step_count();
	completion = current_count * 100 / current_goal; // should move this to a new step counter module

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
}
