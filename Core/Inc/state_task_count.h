/*
 * state_task_count.h
 *
 * Contains functionality for the step counter state of the FSM
 *
 *  Created on: Apr 10, 2025
 *      Author: root
 */

#ifndef STATE_TASK_COUNT_H
#define STATE_TASK_COUNT_H

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "state_task_goal.h" // For reading step goal
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

void increment_steps(uint16_t by);
void decrement_steps(uint16_t by);
uint16_t get_step_count(void);
void toggle_step_unit(void);
void steps_state_task_execute(void);

#endif // STATE_TASK_COUNT_H
