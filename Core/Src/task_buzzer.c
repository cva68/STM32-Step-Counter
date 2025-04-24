/*
 * task_buzzer.c
 *
 *  Created on: Apr 22, 2025
 *      Author: awa158
 */

#include "task_buzzer.h"
#include "buzzer.h"
#include "state_task_goal.h"
#include "state_task_count.h"
#include <stdbool.h>
#include <stdint.h>

#define BUZZER_TIMER_LENGTH 10

uint8_t buzzer_timer = 0;
bool buzzer_on = false;
bool new_goal_set = true;

void buzzer_task_execute(void) {
	if(get_step_count() == get_step_goal()){
		if(new_goal_set == true){
			buzzer_on = true;
			set_buzzer(500);
			new_goal_set = false;
		}
	}else{
		new_goal_set = true;
	}

	if(buzzer_on == true){
		buzzer_timer += 1;
		if(buzzer_timer > BUZZER_TIMER_LENGTH){
			buzzer_on = false;
			set_buzzer(0);
			buzzer_timer = 0;
		}
	}
}
