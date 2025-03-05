/*
 * task_buttons.h
 *
 *  Created on: Mar 6, 2025
 *      Author: awa158
 */

#ifndef TASK_BUTTONS_H
#define TASK_BUTTONS_H

#include "gpio.h"
#include "buttons.h"
#include "rgb.h"

void buttons_task_init(void);
void buttons_task_execute(void);

#endif // TASK_BUTTONS_H
