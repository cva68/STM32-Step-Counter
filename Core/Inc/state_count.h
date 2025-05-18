/*
 * state_count.h
 *
 * Functions for displaying the current step count on the display.
 *
 *  Created on: Apr 10, 2025
 *  	Authors: C. Varney, A. Walker
 */

#ifndef STATE_TASK_COUNT_H
#define STATE_TASK_COUNT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "steps.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

void state_count_toggleUnit(void);
void state_count_executeTask(void);

#endif // STATE_TASK_COUNT_H
