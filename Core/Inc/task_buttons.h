/*
 * task_buttons.h
 *
 * Task to send periodic updates to buttons module (in order to have it raise press flags).
 * Essentially just a passthrough to buttons.c, but this module is kept in between for consistency.
 *
 *  Created on: Mar 6, 2025
 *      Authors: C. Varney, A. Walker
 */

#ifndef TASK_BUTTONS_H
#define TASK_BUTTONS_H

#include "buttons.h"
#include "rgb.h"

void task_buttons_initTask(void);
void task_buttons_executeTask(void);

#endif // TASK_BUTTONS_H
