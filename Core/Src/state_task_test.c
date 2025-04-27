/*
 * state_task_test.c
 *
 * Contains functionality for the test state of the FSM
 *
 *  Created on: Apr 20, 2025
 *      Author: cva68
 */

#include <stdbool.h>
#include <stdio.h>
#include "state_task_test.h"
#include "state_task_count.h" // For getting current number of steps
#include "state_task_goal.h" // For getting current goal
#include "joystick.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

// If the joystick displacement is less than this value, only change the step
// value every second call to the task.
#define FAST_THRESHOLD 40

// Increase RATE_DIVIDER to decrease the speed of change of the step count
#define RATE_DIVIDER 70

static bool skip_step = false;

void test_state_task_execute(void)
{
	struct percentage_coords joystick_pos = get_percentage_coordinates();
	int y = joystick_pos.y;

	// To halve the rate of change if the joystick hasn't exceeded a threshold
	if (y < FAST_THRESHOLD && y > -1 * FAST_THRESHOLD ) {
		if (skip_step) {
			skip_step = false;
			return;
		}
		skip_step = true;
	}

	uint16_t current_goal = get_step_goal();
	uint16_t current_steps = get_step_count();
	uint16_t old_steps = current_steps; // for underflow detection without using negatives

	// Exponential rate of change for finer adjustment
	// Moves faster for a larger upperbound, slower for a smaller upperbound
	int magnitude = (current_goal / 1000) * (y * y) / RATE_DIVIDER;

	if (y > 0) {
		current_steps -= magnitude;
	} else if (y < 0) {
		// In the case where the current steps is greater than the current goal.
		// disallow increasing the step count.
		if (current_steps > current_goal) return;
		current_steps += magnitude;
	}

	current_steps = (current_steps / 10) * 10; // Round to nearest 10

	if (joystick_pos.y < 0 && current_steps > current_goal) current_steps = current_goal; // Exceeded goal
	else if (joystick_pos.y > 0 && current_steps > old_steps) current_steps = 0; // Underflow

	set_step_count(current_steps);

	// Display the step goal
	static char new_step_count[19];
	snprintf(new_step_count, sizeof(new_step_count), "New Steps: %u       ", current_steps);
	ssd1306_WriteString(new_step_count, Font_7x10, White);
}

