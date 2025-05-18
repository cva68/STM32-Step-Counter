/*
 * joystick.c
 *
 * Driver for the joystick module of the RCAP Expansion Board. Can be used in either
 * a "analog" mode (% values in X and Y direction), or "digital" mode (boolean flags
 * raised for up, down, left and right directions)
 *
 *  Created on: Mar 5, 2025
 *  	Authors: C. Varney, A. Walker
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "joystick.h"
#include "adc_controller.h"

// Rest position of the joystick
#define MIDDLE_ADC_VALUE 2047

// Percentage distance the joystick must be moved before registering any motion
#define DRIFT_THRESHOLD 20

// Percentage distance the joystick must be moved before raising a UP/DOWN/L/R flag
#define FLAG_RAISE_THRESHOLD 30

static struct joystick_position_flags flags = {0};

struct percentage_coords joystick_getPercentageCoords(void) {
	// Convert raw values to percentage values, stored in percentage_coords struct
	struct percentage_coords output;
	uint16_t* raw_values = adcController_getValues();
	output.x = (((int16_t)raw_values[2] - MIDDLE_ADC_VALUE) * 100) / MIDDLE_ADC_VALUE;
	output.y = (((int16_t)raw_values[1] - MIDDLE_ADC_VALUE) * 100) / MIDDLE_ADC_VALUE;

	// Filter out drift
	if (output.x < DRIFT_THRESHOLD && output.x > -1 * DRIFT_THRESHOLD) output.x = 0;
	if (output.y < DRIFT_THRESHOLD && output.y > -1 * DRIFT_THRESHOLD) output.y = 0;

	return output;
}

void joystick_update(void) {
	// Update the stored position flags
	// These get reset when get_joystick_position_flags is called
	struct percentage_coords percentages;
	percentages = joystick_getPercentageCoords();

	if (percentages.x > FLAG_RAISE_THRESHOLD) {
		flags.left = true;
	} else if (percentages.x < -1 * FLAG_RAISE_THRESHOLD) {
		flags.right = true;
	}

	if (percentages.y > FLAG_RAISE_THRESHOLD) {
		flags.down = true;
	} else if (percentages.y < -1 * FLAG_RAISE_THRESHOLD) {
		flags.up = true;
	}
}

struct joystick_position_flags joystick_getFlags(void) {
	// Return any raised position flags

	// Store the current flags
	struct joystick_position_flags flagsToReturn = flags;

	// Reset the flags to all be false
	flags.left = 0;
	flags.right = 0;
	flags.up = 0;
	flags.down = 0;

	// Return the flag values, prior to when they were reset
	return flagsToReturn;
}
