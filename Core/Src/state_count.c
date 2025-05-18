/*
 * state_task_count.c
 *
 * Functions for displaying the current step count on the display.
 *
 *  Created on: Apr 10, 2025
 *  	Authors: C. Varney, A. Walker
 */

#include <stdbool.h>
#include <stdio.h>
#include "steps.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

// Boolean for selecting units (count/%, km/yd)
static bool steps_as_percentage = false;

void state_count_toggleUnit(void)
{
	steps_as_percentage = !(steps_as_percentage);
}

void state_count_executeTask(void)
{
	// Display the step count
	static char count[19];

	if (steps_as_percentage) {
		uint16_t step_percentage = (steps_getStepCount() * 100) / steps_getStepGoal(); // avoid floats
		snprintf(count, sizeof(count), "Steps: %u%% goal  ", step_percentage);
	} else {
		snprintf(count, sizeof(count), "Steps: %u         ", steps_getStepCount());
	}

	ssd1306_WriteString(count, Font_7x10, White);
}
