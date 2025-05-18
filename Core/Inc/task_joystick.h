/*
 * task_joystick.h
 *
 * Task to send periodic updates to joystick module (in order to have it update percentage values and
 * raise direction flags). Essentially just a passthrough to joystick.c, but this module is kept in 
 * between for consistency.
 *
 *  Created on: Mar 6, 2025
 *      Authors: C. Varney, A. Walker
 */

#ifndef JOYSTICK_H
#define JOYSTICK_H

void task_joystick_executeTask(void);

#endif // JOYSTICK_H


