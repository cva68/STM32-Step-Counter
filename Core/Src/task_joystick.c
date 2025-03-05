/*
 * task_joystick.c
 *
 *  Created on: Mar 6, 2025
 *      Author: awa158
 */

#include "adc.h"
#include "task_joystick.h"

static uint16_t raw_adc[2];

void joystick_task_execute(void) {
	// Update the ADC values of the JoyStick X and Y axis inputs
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)raw_adc, 2);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc) {

}

uint16_t* get_raw_values(void) {
	return raw_adc;
}

