/*
 * task_buzzer.c
 *
 * Task to turn the buzzer on when the step goal is reached.
 *
 *  Created on: Apr 22, 2025
 *      Authors: C. Varney, A. Walker
 */

#include <stdbool.h>
#include <stdint.h>
#include "task_buzzer.h"
#include "buzzer.h"
#include "steps.h"

#define BUZZER_TIMER_LENGTH 10

void task_buzzer_initTask(void)
{
	buzzer_init();
}

// Turn the buzzer on when the goal is reached
void task_buzzer_executeTask(void)
{
	static uint8_t buzzer_timer = 0;
	static bool buzzer_on = false;
	static bool new_goal_set = true; // When the goal changes, raise this flag

	if (steps_getStepCount() >= steps_getStepGoal()) {
		// If we haven't already sounded the buzzer for this goal, do so now
		if (new_goal_set) {
			buzzer_on = true;
			buzzer_set(500);
			new_goal_set = false;
		}
	} else {
		new_goal_set = true;
	}

	if (buzzer_on){
		// Turn the buzzer off after BUZZER_TIMER_LENGTH
		buzzer_timer += 1;
		if (buzzer_timer > BUZZER_TIMER_LENGTH){
			buzzer_on = false;
			buzzer_set(0);
			buzzer_timer = 0;
		}
	}
}
