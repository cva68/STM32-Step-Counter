/*
 * task_buttons.c
 *
 * Task to send periodic updates to buttons module (in order to have it raise press flags).
 * Essentially just a passthrough to buttons.c, but this module is kept in between for consistency.
 *
 *  Created on: Mar 6, 2025
 *      Authors: C. Varney, A. Walker
 */

#include <stdbool.h>
#include "task_buttons.h"
#include "buttons.h"

void task_buttons_initTask(void) {
	// Initialise the upstream button driver, enable all RGB LED colour channels.
	buttons_init();
}

void task_buttons_executeTask(void) {
	// Update the button flags
	buttons_update();
}