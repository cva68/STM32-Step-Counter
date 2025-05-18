/*
 * adc_controller.h
 *
 * Module to start DMA on the ADC channel connected to the joystick and pot,
 * and to return raw data from these channels.
 *
 *  Created on: Apr 20, 2025
 *      Authors: C. Varney, A. Walker
 */

#include <stdint.h>
#include "gpio.h"
#include "adc.h"

#ifndef ADC_CONTROLLER_H
#define ADC_CONTROLLER_H

void adcController_update(void);
uint16_t* adcController_getValues(void);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);


#endif // ADC_CONTROLLER_H
