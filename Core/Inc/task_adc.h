/*
 * task_adc.h
 *
 *  Created on: Apr 14, 2025
 *      Author: cva68
 */

#ifndef TASK_POT_H
#define TASK_POT_H

#include "gpio.h"

void adc_task_execute(void);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);

#endif /* INC_TASK_POT_H */
