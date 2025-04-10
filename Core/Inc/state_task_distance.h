/*
 * state_task_distance.h
 *
 * Contains functionality for the distance state of the FSM
 *
 *  Created on: Apr 10, 2025
 *      Author: root
 */

#ifndef STATE_TASK_DISTANCE_H
#define STATE_TASK_DISTANCE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"
#include "state_task_count.h" // For reading step goal

void toggle_distance_unit(void);
void distance_state_task_execute(void);

#endif // STATE_TASK_DISTANCE_H

