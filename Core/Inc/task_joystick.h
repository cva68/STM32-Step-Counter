/*
 * task_joystick.h
 *
 *  Created on: Mar 6, 2025
 *      Author: awa158
 */

#ifndef JOYSTICK_H
#define JOYSTICK_H

void joystick_task_execute(void);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
uint16_t* get_raw_values(void);

// To Do: Function to return x/y values as positions between 0 and 100 (need much further abstraction than get_raw_values)

#endif // JOYSTICK_H


