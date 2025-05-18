/*
 * task_joystick.c
 *
 * Task to send periodic updates to joystick module (in order to have it update percentage values and
 * raise direction flags). Essentially just a passthrough to joystick.c, but this module is kept in 
 * between for consistency.
 *
 *  Created on: Mar 6, 2025
 *      Authors: C. Varney, A. Walker
 */

#include "task_joystick.h"
#include "joystick.h"

void task_joystick_executeTask(void) {
	// Update the ADC values of the joystick X and Y axis inputs
	joystick_update();
}
