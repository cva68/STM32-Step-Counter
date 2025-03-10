/*
 * task_joystick.c
 *
 *  Created on: Mar 6, 2025
 *      Author: awa158
 */

#include "adc.h"
#include "task_joystick.h"
#include "joystick.h"

void joystick_task_execute(void) {
	// Update the ADC values of the JoyStick X and Y axis inputs
	update_joystick();
}
