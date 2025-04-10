/*
 * task_fsm.c
 *
 * Task to switch between FSM states based on joystick / button inputs
 *
 *  Created on: Apr 9, 2025
 *      Author: connor
 */

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

void fsm_state_entry(state_t state);

void fsm_task_execute(void);

