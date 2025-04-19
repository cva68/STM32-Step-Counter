/*
 * pot.c
 *
 *  Created on: Apr 14, 2025
 *      Author: awa158
 */

#include "adc.h"

static uint16_t pot_raw_adc[3];

void update_pot(void) {
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)pot_raw_adc, 3);
}

uint16_t get_pot_raw_values(void) {
	// Return raw values (between 0 and 4096) of the analog inputs of the joysticks
	uint16_t vr1_value = pot_raw_adc[0];
	return vr1_value;
}

