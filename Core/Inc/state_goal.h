/*
 * state_goal.h
 *
 * Functions for displaying and modifying the goal on the display.
 *
 *  Created on: Apr 10, 2025
 *      Authors: C. Varney, A. Walker
 */

#ifndef STATE_TASK_GOAL_H
#define STATE_TASK_GOAL_H

#include <stdio.h>
#include <stdint.h>
#include "steps.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

void state_goal_executeDisplayTask(void);
void state_goal_executeModifyTask(void);
void state_goal_updateGoal();

#endif // STATE_TASK_GOAL_H
