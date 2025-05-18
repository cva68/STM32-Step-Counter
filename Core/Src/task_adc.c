/*
 * task_adc.c
 *
 * Task to update the ADC values periodically.
 * Essentially just a passthrough to adc.c, but this module is kept in between for consistency.
 *
 *  Created on: Apr 14, 2025
 *      Authors: C. Varney, A. Walker
 */

#include "task_adc.h"
#include "adc_controller.h"

void task_adc_executeTask(void)
{
	adcController_update();
}
