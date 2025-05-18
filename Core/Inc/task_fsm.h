/*
 * task_display_fsm.h
 *
 * Task to switch between FSM states based on joystick / button inputs.
 *
 *  Created on: Apr 9, 2025
 *      Authors: C. Varney, A. Walker
 */

#ifndef TASK_DISPLAY_FSM_H
#define TASK_DISPLAY_FSM_H

#include <stdio.h>
#include <stdbool.h>
#include "joystick.h"
#include "buttons.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

#include "state_count.h"
#include "state_distance.h"
#include "state_goal.h"
#include "state_test.h"

typedef enum {
    STATE_STEPS,
    STATE_DISTANCE,
    STATE_GOAL,
    STATE_MODIFY_GOAL,
	STATE_TEST
} state_t;

void task_fsm_initTask(void);
void task_fsm_updateDisplay(state_t state);
void task_fsm_taskExecute(void);

#endif // TASK_DISPLAY_FSM_H

