/*
 * pot.c
 *
 *  Created on: Apr 14, 2025
 *      Author: awa158
 */

// Values for mapping ADC values to step goal values
#define GOAL_RANGE 14500
#define ADC_RANGE 3956
#define GOAL_MIN 500
#define ADC_MIN 139

#include "adc_controller.h"


uint16_t get_scaled_pot_value(void) {
	// Scale the ADC value to a number between 500 and 15,000
	uint16_t vr1_adc = get_adc_values()[0];
	uint16_t new_goal = ((GOAL_RANGE * (vr1_adc - ADC_MIN)) / ADC_RANGE) + GOAL_MIN; // Convert ADC to goal value
	new_goal = (new_goal / 100) * 100; // Round down to nearest 100

	// Ensure the goal stays above 500, even when the ADC drops below the stated minimum
	if(new_goal < 500) new_goal = 500;

	return new_goal;
}
