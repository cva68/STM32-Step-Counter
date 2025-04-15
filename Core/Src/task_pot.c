/*
 * task_pot.c
 *
 *  Created on: Apr 14, 2025
 *      Author: awa158
 */

#include "task_pot.h"
#include "pot.h"

void pot_task_execute(void) {
	// Update the ADC values of the Potentiometer
	update_pot();
}
