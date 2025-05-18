/*
* steps.c
*
* Stores step goal and step count, providing getter and setter functions.
*
*  Created on: May 5, 2025
*      Author: cva68
*/

#include <stdint.h>

static uint16_t step_goal = 1000;
static uint16_t step_count = 0;

// Step count getters and setters
void steps_incrementSteps(uint16_t by)
{
	// Increase the step count
    step_count += by;
}

void steps_decrementSteps(uint16_t by)
{
	// Decrease the step count
    step_count -= by;
}

void steps_setStepCount(uint16_t steps)
{
	// Increase the step count
    step_count = steps;
}

uint16_t steps_getStepCount(void)
{
	// Get the step count
    return step_count;
}

void steps_setStepGoal(uint16_t goal)
{
	// Set the step goal
    step_goal = goal;
}

uint16_t steps_getStepGoal()
{
	// Get the current step goal
	return step_goal;
}

void steps_incrementStepGoal(uint16_t by)
{
	// Increment the step goal
    step_goal += by;
}

uint16_t steps_getGoalPercentage(void) 
{
    // Return the current percentage completion of the goal
    uint16_t step_percentage = (step_count * 100) / step_goal;
    return step_percentage;
}
