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
#include "pot.h"

static uint16_t step_goal = 1000;
static uint16_t new_goal;


void set_step_goal(uint16_t goal) {
	// Set the step goal
    step_goal = goal;
}

uint16_t get_step_goal() {
	// Get the current step goal
	return step_goal;
}

void update_step_goal() {
	// Transfer the static new_goal value to the actual step_goal
	set_step_goal(new_goal);
}

void modify_state_task_execute(void)
{
	// Get the pot value
	new_goal = get_scaled_pot_value();

	// Display the step goal
	static char goal[19];
	snprintf(goal, sizeof(goal), "New Goal: %u        ", new_goal);
	ssd1306_WriteString(goal, Font_7x10, White);
}

void goal_state_task_execute(void)
{
	// State to display the step goal
	static char goal[18];
	snprintf(goal, sizeof(goal), "Goal: %u           ", step_goal);
	ssd1306_WriteString(goal, Font_7x10, White);
}
