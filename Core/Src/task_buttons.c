/*
 * task_buttons.c
 *
 *  Created on: Mar 6, 2025
 *      Author: awa158
 */

#include "task_buttons.h"
#include "gpio.h"
#include "buttons.h"
#include "rgb.h"
#include "tim.h"

void buttons_task_init(void) {
	// Initialise the upstream button driver, enable all RGB LED colour channels.
	buttons_init();
	rgb_colour_on(RGB_RED);
	rgb_colour_on(RGB_GREEN);
	rgb_colour_on(RGB_BLUE);

	// Start the PWM timer associated with RGB_UP (DS3)
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
}

void buttons_task_execute(void) {
	// Update the RGB LEDs depending on which button is pressed.
	buttons_update();

	// This is disabled to allow PWM control of RGB_UP (DS3)
	//if (buttons_checkButton(UP) == PUSHED) {
	//	rgb_led_toggle(RGB_UP);
	//}

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
