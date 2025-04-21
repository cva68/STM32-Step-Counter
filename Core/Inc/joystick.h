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

struct joystick_position_flags
{
	bool left;
	bool right;
	bool up;
	bool down;
};


void update_joystick(void);
struct percentage_coords get_percentage_coordinates(void);
struct joystick_position_flags get_joystick_flags(void);

#endif // JOYSTICK_H
