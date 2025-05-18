/*
 * state_goal.c
 *
 * Functions for displaying and modifying the goal on the display.
 *
 *  Created on: Apr 10, 2025
 *      Authors: C. Varney, A. Walker
 */

#include <stdbool.h>
#include <stdio.h>
#include "state_goal.h"
#include "steps.h"
#include "pot.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

static uint16_t new_goal; // When modifying the goal, store the value here

void state_goal_updateGoal()
{
	// Transfer the static new_goal value to the actual step_goal
	steps_setStepGoal(new_goal);
}

void state_goal_executeModifyTask(void)
{
	// Get the pot value
	new_goal = pot_getScaledValue();

	// Display the step goal
	static char goal[19];
	snprintf(goal, sizeof(goal), "New Goal: %u        ", new_goal);
	ssd1306_WriteString(goal, Font_7x10, White);
}

void state_goal_executeDisplayTask(void)
{
	// State to display the step goal
	static char percentage_goal[19];
	snprintf(percentage_goal, sizeof(percentage_goal), "Goal: %u%% / %u     ",
			 steps_getGoalPercentage(), steps_getStepGoal());
	ssd1306_WriteString(percentage_goal, Font_7x10, White);
}
