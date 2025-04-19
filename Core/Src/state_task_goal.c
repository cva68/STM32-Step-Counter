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

// Values for mapping ADC values to step goal values
#define GOAL_RANGE 14500
#define ADC_RANGE 3956
#define GOAL_MIN 500
#define ADC_MIN 139

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
	// State to modify the step goal
	uint16_t vr1_adc = get_pot_raw_values();
	new_goal = ((GOAL_RANGE * (vr1_adc - ADC_MIN)) / ADC_RANGE) + GOAL_MIN; // Convert ADC to goal value
	new_goal = (new_goal / 100) * 100; // Round down to nearest 100

	// Ensure the goal stays above 500, even when the ADC drops below the stated minimum
	if(new_goal < 500) new_goal = 500;

	// Display the step goal
	static char goal[18];
	snprintf(goal, sizeof(goal), "New Goal: %u\n", new_goal);
	ssd1306_WriteString(goal, Font_7x10, White);
}

void goal_state_task_execute(void)
{
	// State to display the step goal
	static char goal[18];
	snprintf(goal, sizeof(goal), "Goal: %u\n", step_goal);
	ssd1306_WriteString(goal, Font_7x10, White);
}
