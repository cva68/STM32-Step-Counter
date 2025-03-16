/*
 * task_buttons.c
 *
 *  Created on: Mar 6, 2025
 *      Author: awa158
 */

#include "task_buttons.h"
#include "buttons.h"
#include "rgb.h"
#include "pwm.h"

#include <stdbool.h>

void buttons_task_init(void) {
	// Initialise the upstream button driver, enable all RGB LED colour channels.
	buttons_init();
	rgb_colour_on(RGB_RED);
	rgb_colour_on(RGB_GREEN);
	rgb_colour_on(RGB_BLUE);

	// Start the PWM timer associated with RGB_UP (DS3)
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
}

bool buttons_task_execute(void) {
	// Updates LEDs based on button input
	// Returns the state of SW2, to be passed to the task_uart layer

	static uint8_t dutyCycle = 0;
	static bool SW2_state = 0;

	// Update the RGB LEDs depending on which button is pressed.
	buttons_update();

	// This doesn't use rgb.h, as it does not support PWM
	if (buttons_checkButton(UP) == PUSHED) {
		dutyCycle = (dutyCycle + 10) % 125;
		if (dutyCycle > 100) dutyCycle = 0;
		pwm_setDutyCycle(&htim2, TIM_CHANNEL_3, dutyCycle);
	}

	if (buttons_checkButton(DOWN) == PUSHED) {
		SW2_state = !SW2_state;
		rgb_led_toggle(RGB_DOWN);
	}

	if (buttons_checkButton(LEFT) == PUSHED) {
		rgb_led_toggle(RGB_LEFT);
	}

	if (buttons_checkButton(RIGHT) == PUSHED) {
		rgb_led_toggle(RGB_RIGHT);
	}

	return SW2_state;
}
