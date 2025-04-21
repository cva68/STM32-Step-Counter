/*
 * state_task_goal.h
 *
 * Contains functionality for the step goal states of the FSM
 *
 *  Created on: Apr 10, 2025
 *      Author: root
 */

#ifndef STATE_TASK_GOAL_H
#define STATE_TASK_GOAL_H

#include <stdio.h>
#include <stdint.h>
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

void modify_state_task_execute(void);
void set_step_goal(uint16_t goal);
void increment_step_goal(uint16_t by);
uint16_t get_step_goal();
void update_step_goal();
void goal_state_task_execute(void);

#endif // STATE_TASK_GOAL_H
