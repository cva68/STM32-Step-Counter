/*
 * state_task_modify.c
 *
 *  Created on: Apr 14, 2025
 *      Author: awa158
 */

#include <stdbool.h>
#include <stdio.h>
#include "state_task_modify.h"
#include "state_task_goal.h"
#include "pot.h"

#define GOAL_RANGE 14500
#define ADC_RANGE 3956
#define GOAL_MIN 500
#define ADC_MIN 139

uint16_t new_goal;

void modify_state_task_execute(void)
{
	uint16_t vr1_adc = get_pot_raw_values();
	new_goal = ((GOAL_RANGE * (vr1_adc - ADC_MIN)) / ADC_RANGE) + GOAL_MIN;

	//goes slightly below 500 to 453 so sad :( only in 2025 am I right
	if(new_goal < 500)
	{
		new_goal = 500;
	}
	// Display the step goal
	static char goal[18];
	snprintf(goal, sizeof(goal), "New Goal: %u\n", new_goal);
	ssd1306_WriteString(goal, Font_7x10, White);
}

void set_new_goal(void){
	set_step_goal(new_goal);
}
