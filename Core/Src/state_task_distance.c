/*
 * state_task_distance.c
 *
 * Contains functionality for the distance state of the FSM
 *
 *  Created on: Apr 10, 2025
 *      Author: root
 */

#include <stdbool.h>
#include <stdio.h>
#include "state_task_distance.h"
#include "state_task_count.h" // For getting current number of steps

// Define conversion rates
#define CM_PER_STEP 80
#define KILOMETRES_TO_YARDS 1093

// Boolean for selecting units (km/yd)
static bool distance_in_yards = false;

void toggle_distance_unit(void) {
	distance_in_yards = !(distance_in_yards);
}

void distance_state_task_execute(void)
{
	// Calculate the distance walked, in meters, avoiding floats
	static char distance_string[18];
	uint16_t meters = ((uint32_t)get_step_count() * CM_PER_STEP) / 100;

	// Convert to yards if requested
	if (distance_in_yards) {
		uint16_t yards = ((uint32_t)meters * KILOMETRES_TO_YARDS) / 1000;
		snprintf(distance_string, sizeof(distance_string), "Dist: %uyd", yards);
	} else {
		// Split into kilometers and meters
		uint16_t kilometers = meters / 1000; // 2600 = 2
		uint16_t remainder_meters = meters % 1000; // = 600
		snprintf(distance_string, sizeof(distance_string), "Dist: %u.%03ukm", kilometers, remainder_meters);
	}

	ssd1306_WriteString(distance_string, Font_7x10, White);
}

