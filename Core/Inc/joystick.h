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

#include <stdbool.h>
#include <stdint.h>
#include "gpio.h"

// Data structure for storing percentage coordinates
struct percentage_coords
{
	int8_t x;
	int8_t y;
};

// Data structure for storing string representations of percentage coordinates
struct coord_strings
{
	char x[14];
	char y[14];
};

struct joystick_position_flags
{
	bool left;
	bool right;
	bool up;
	bool down;
	bool short_press;
	bool long_press;
};

// HW level functions
void update_joystick(void);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);
uint16_t* get_raw_values(void);

// Abstraction functions
struct percentage_coords get_percentage_coordinates(void);
struct coord_strings get_coordinate_strings(void);
struct joystick_position_flags get_joystick_flags(void);
char *raw_adc_as_string(void);

#endif // JOYSTICK_H
