/*
 * joystick.h
 *
 * Driver for the joystick module of the RCAP Expansion Board. Can be used in either
 * a "analog" mode (% values in X and Y direction), or "digital" mode (boolean flags
 * raised for up, down, left and right directions)
 *
 *  Created on: Mar 5, 2025
 *  	Authors: C. Varney, A. Walker
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


void joystick_update(void);
struct percentage_coords joystick_getPercentageCoords(void);
struct joystick_position_flags joystick_getFlags(void);

#endif // JOYSTICK_H
