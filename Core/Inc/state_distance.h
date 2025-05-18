/*
 * state_distance.h
 *
 * Functions for displaying the walked distance on the display.
 *
 *  Created on: Apr 10, 2025
 *  	Authors: C. Varney, A. Walker
 */

#ifndef STATE_TASK_DISTANCE_H
#define STATE_TASK_DISTANCE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"
#include "steps.h"

void state_distance_toggleUnit(void);
void state_distance_executeTask(void);

#endif // STATE_TASK_DISTANCE_H

