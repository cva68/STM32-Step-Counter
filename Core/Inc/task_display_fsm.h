/*
 * task_display_fsm.c
 *
 * Task to switch between FSM states based on joystick / button inputs
 *
 *  Created on: Apr 9, 2025
 *      Author: connor
 */

#ifndef TASK_DISPLAY_FSM_H
#define TASK_DISPLAY_FSM_H

#include "joystick.h"
#include "buttons.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"
#include <stdio.h>
#include <stdbool.h>

#include "state_task_goal.h"
#include "state_task_count.h"
#include "state_task_distance.h"

typedef enum {
    STATE_STEPS,
    STATE_DISTANCE,
    STATE_GOAL,
    STATE_MODIFY_GOAL,
	STATE_TEST
} state_t;

state_t get_display_state(void);

void display_fsm_task_init(void);

void update_fsm_display(state_t state);

void display_fsm_task_execute(void);

#endif // TASK_DISPLAY_FSM_H

