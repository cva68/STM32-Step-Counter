/*
 * joystick.c
 *
 * Driver for the JoyStick module of the RCAP Expansion Board.
 *
 *  Created on: Mar 5, 2025
 *      Author: cva68
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "adc.h"
#include "joystick.h"

#define MIDDLE_ADC_VALUE 2047

static uint16_t raw_adc[2];

void update_joystick(void) {
	// Update the ADC values of the JoyStick X and Y axis inputs
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);

	// Do something here to detect press and hold
	// (although maybe we should just extend button.c?)
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	// No callback required as of yet
}


uint16_t* get_raw_values(void) {
	// Return raw values (between 0 and 4096) of the analog inputs of the joysticks
	return raw_adc;
}

struct percentage_coords get_percentage_coordinates(void) {
	// Convert raw values to percentage values, stored in percentage_coords struct
	struct percentage_coords output;
	output.x = (((int16_t)raw_adc[1] - MIDDLE_ADC_VALUE) * 100) / MIDDLE_ADC_VALUE;
	output.y = (((int16_t)raw_adc[0] - MIDDLE_ADC_VALUE) * 100) / MIDDLE_ADC_VALUE;

	return output;
}

struct coord_strings get_coordinate_strings(void) {
	// Get a coord_strings struct, containing two lines with string descriptors of the joystick position
	struct percentage_coords percentages;
	percentages = get_percentage_coordinates();

	const char *x_direction;
	const char *y_direction;

	if (percentages.x > 10) {
	    x_direction = "Left";
	} else if (percentages.x < -10) {
	    x_direction = "Right";
	} else {
	    x_direction = "Rest";
	}

	if (percentages.y > 10) {
	    y_direction = "Down";
	} else if (percentages.y < -10) {
	    y_direction = "Up";
	} else {
	    y_direction = "Rest";
	}

	struct coord_strings output;

	if (strcmp(y_direction, "Rest") == 0) {
		snprintf(output.y, sizeof(output.y), "%s", y_direction);
	} else {
		snprintf(output.y, sizeof(output.y), "%s,%u%%\r\n", y_direction, abs(percentages.y));
	}

	if (strcmp(x_direction, "Rest") == 0) {
		snprintf(output.x, sizeof(output.x), "%s", x_direction);
	} else {
		snprintf(output.x, sizeof(output.x), "%s,%u%%\r\n", x_direction, abs(percentages.x));
	}

	return output;
}

struct joystick_position_flags get_joystick_flags(void) {
	struct percentage_coords percentages;
	percentages = get_percentage_coordinates();

	struct joystick_position_flags flags = {0};

	if (percentages.x > 10) {
		flags.left = true;
	} else if (percentages.x < -10) {
		flags.right = true;
	}

	if (percentages.y > 10) {
		flags.down = true;
	} else if (percentages.y < -10) {
		flags.up = true;
	}

	return flags;

	// Presses not yet implemented (although maybe we should just extend button.c?)
}

char *raw_adc_as_string(void) {
	// Returns the raw ADC values as a string
	static char raw[14];
	snprintf(raw, sizeof(raw), "%u,%u\r\n", raw_adc[0], raw_adc[1]);
	return raw;
}

