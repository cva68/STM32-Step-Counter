/*
 * state_task_count.c
 *
 * Contains functionality for the step counter / step goal / distance states of the FSM
 *
 *  Created on: Apr 10, 2025
 *      Author: root
 */

#include <stdbool.h>
#include <stdio.h>
#include "state_task_count.h"
#include "state_task_goal.h" // For reading step goal

// Define conversion rates
#define CM_PER_STEP 80
#define KILOMETRES_TO_YARDS 1093

// Variable to store step count
static uint16_t step_count = 0;

// Boolean for selecting units (count/%, km/yd)
static bool steps_as_percentage = false;

void increment_steps(uint16_t by) {
	// Increase the step count
    step_count += by;
}

void decrement_steps(uint16_t by) {
	// Decrease the step count
    step_count -= by;
}

uint16_t get_step_count(void) {
	// Get the step count
    return step_count;
}

void toggle_step_unit(void) {
	steps_as_percentage = !(steps_as_percentage);
}


void steps_state_task_execute(void)
{
	// Display the step count
	static char count[19];
	if (steps_as_percentage) {
		uint16_t step_percentage = (step_count * 100) / get_step_goal(); // avoid floats
		snprintf(count, sizeof(count), "Steps: %u%% goal  ", step_percentage);
	} else {
		snprintf(count, sizeof(count), "Steps: %u         ", step_count);
	}
	ssd1306_WriteString(count, Font_7x10, White);
}
