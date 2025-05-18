/*
 * state_distance.c
 *
 * Functions for displaying the walked distance on the display.
 *
 *  Created on: Apr 10, 2025
 *  	Authors: C. Varney, A. Walker
 */

#include <stdbool.h>
#include <stdio.h>
#include "state_distance.h"
#include "steps.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

// Define conversion rates
#define CM_PER_STEP 90
#define KILOMETRES_TO_YARDS 1093

// Boolean for selecting units (km/yd)
static bool distance_in_yards = false;

void state_distance_toggleUnit(void) {
	distance_in_yards = !(distance_in_yards);
}

void state_distance_executeTask(void)
{
	// Calculate the distance walked, in meters, avoiding floats
	static char distance_string[19];
	uint16_t meters = ((uint32_t)steps_getStepCount() * CM_PER_STEP) / 100;

	// Convert to yards if requested
	if (distance_in_yards) {
		uint16_t yards = ((uint32_t)meters * KILOMETRES_TO_YARDS) / 1000;
		snprintf(distance_string, sizeof(distance_string), "Dist: %uyd          ", yards);
	} else {
		// Split into kilometers and meters
		uint16_t kilometers = meters / 1000; // 2600 = 2
		uint16_t remainder_meters = meters % 1000; // = 600
		snprintf(distance_string, sizeof(distance_string), "Dist: %u.%03ukm      ", kilometers, remainder_meters);
	}

	ssd1306_WriteString(distance_string, Font_7x10, White);
}

