/*
 * task_buttons.c
 *
 *  Created on: Mar 6, 2025
 *      Author: awa158
 */

#define INCREMENT_SIZE 80

#include "task_buttons.h"
#include "buttons.h"
#include "state_task_count.h"
#include "task_display_fsm.h"

#include <stdbool.h>

void buttons_task_init(void) {
	// Initialise the upstream button driver, enable all RGB LED colour channels.
	buttons_init();
}

bool buttons_task_execute(void) {
	// Update the button flags, and increment the step count if SW2 is pressed
	buttons_update();
	if (get_display_state() != STATE_MODIFY_GOAL) {
		if (buttons_checkButton(UP) == PUSHED) increment_steps(INCREMENT_SIZE);
	} else {
		buttons_checkButton(UP); // Clear flags
	}
}
