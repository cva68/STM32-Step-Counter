/*
 * task_pot.c
 *
 *  Created on: Apr 14, 2025
 *      Author: awa158
 */

#include "task_adc.h"
#include "adc_controller.h"

void adc_task_execute(void) {
	adc_controller_update();
}
