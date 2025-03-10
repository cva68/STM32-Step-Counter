/*
 * joystick.c
 *
 * Driver for the JoyStick module of the RCAP Expansion Board.
 *
 *  Created on: Mar 5, 2025
 *      Author: cva68
 */

#include "adc.h"
#include "joystick.h"

static uint16_t raw_adc[2];


void update_joystick(void) {
	// Update the ADC values of the JoyStick X and Y axis inputs
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {

}

uint16_t* get_raw_values(void) {
	return raw_adc;
}

