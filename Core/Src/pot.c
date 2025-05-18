/*
 * pot.c
 *
 * Potentiometer abstraction, handles scaling from raw values to reasonable
 * step goal values (between 500 and 15000)
 *
 *  Created on: Apr 14, 2025
 *  	Authors: C. Varney, A. Walker
 */

// Values for mapping ADC values to step goal values
#define GOAL_RANGE 14500
#define ADC_RANGE 3956
#define GOAL_MIN 500
#define ADC_MIN 139

#include <stdint.h>
#include "pot.h"
#include "adc_controller.h"

uint16_t pot_getRawValue(void) {
	// 0th returned ADC value is the potentiometer
	uint16_t vr1_adc = adcController_getValues()[0];
	return vr1_adc;
}

uint16_t pot_getScaledValue(void) {
	// Scale the ADC value to a number between 500 and 15,000
	uint16_t new_goal = ((GOAL_RANGE * (pot_getRawValue() - ADC_MIN)) / ADC_RANGE) + GOAL_MIN; // Convert ADC to goal value
	new_goal = (new_goal / 100) * 100; // Round down to nearest 100

	// Ensure the goal stays above 500, even when the ADC drops below the stated minimum
	if(new_goal < 500) new_goal = 500;

	return new_goal;
}
