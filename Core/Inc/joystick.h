/*
 * joystick.h
 *
 * Driver for the JoyStick module of the RCAP Expansion Board.
 *
 *  Created on: Mar 5, 2025
 *      Author: cva68
 */

#ifndef JOYSTICK_H
#define JOYSTICK_H

void update_joystick(void);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
uint16_t* get_raw_values(void);

// To Do: Function to return x/y values as positions between 0 and 100 (need much further abstraction than get_raw_values)

#endif // JOYSTICK_H
