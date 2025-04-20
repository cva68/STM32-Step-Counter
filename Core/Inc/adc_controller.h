/*
 * adc_controller.h
 *
 * Module to start DMA on the ADC channel connected to the joystick and pot,
 * and to return raw data from these channels.
 *
 * Because we are regularly reading 3 ADC channels, ADC is configured for
 * continuous scan and continuous conversion, with a circular buffer (unlike
 * in the labs, which used single conversion and no buffer)
 *
 *
 *  Created on: Apr 20, 2025
 *      Author: cva68
 */

#include <stdint.h>
#include "gpio.h"
#include "adc.h"

#ifndef ADC_CONTROLLER_H
#define ADC_CONTROLLER_H

void adc_controller_update(void);
uint16_t* get_adc_values(void);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);

#endif // ADC_CONTROLLER_H
