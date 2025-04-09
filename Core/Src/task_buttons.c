/*
 * task_buttons.c
 *
 *  Created on: Mar 6, 2025
 *      Author: awa158
 */

#include "task_buttons.h"
#include "buttons.h"

#include <stdbool.h>

void buttons_task_init(void) {
	// Initialise the upstream button driver, enable all RGB LED colour channels.
	buttons_init();
}

bool buttons_task_execute(void) {
	buttons_update();
}
