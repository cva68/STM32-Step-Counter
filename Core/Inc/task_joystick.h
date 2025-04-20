/*
 * task_joystick.h
 *
 *  Created on: Mar 6, 2025
 *      Author: awa158
 */

#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "gpio.h"

void joystick_task_execute(void);

// To Do: Function to return x/y values as positions between 0 and 100 (need much further abstraction than get_raw_values)

#endif // JOYSTICK_H


