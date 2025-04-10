/*
 * state_task_goal.c
 *
 * Contains functionality for the step goal states of the FSM
 *
 *  Created on: Apr 10, 2025
 *      Author: root
 */

#include <stdbool.h>
#include <stdio.h>
#include "state_task_goal.h"

static uint16_t step_goal = 1000;


void set_step_goal(uint16_t goal) {
    step_goal = goal;
}

uint16_t get_step_goal() {
	return step_goal;
}


void goal_state_task_execute(void)
{
	// Display the step goal
	static char goal[18];
	snprintf(goal, sizeof(goal), "Goal: %u\n", step_goal);
	ssd1306_WriteString(goal, Font_7x10, White);
}
