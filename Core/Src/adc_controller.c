/*
 * adc_controller.c
 *
 * Module to start DMA on the ADC channel connected to the joystick and pot,
 * and to return raw data from these channels.
 *
 *  Created on: Apr 20, 2025
 *      Author: cva68
 */

#include <stdint.h>
#include "gpio.h"
#include "adc_controller.h"
#include "adc.h"

static uint16_t raw_adc[3];

void adc_controller_update(void) {
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 3);
	return;
}

uint16_t* get_adc_values(void) {
    return raw_adc;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {
	// No callback required as of yet
}
