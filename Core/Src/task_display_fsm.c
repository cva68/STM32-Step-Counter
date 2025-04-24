/*
 * task_fsm.c
 *
 * Task to update the display based on an FSM, with states based on joystick / button inputs
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
#include "state_task_test.h"

#define STATE_CHANGE_DELAY 400 // Ticks


typedef enum {
    STATE_STEPS,
    STATE_DISTANCE,
    STATE_GOAL,
    STATE_MODIFY_GOAL,
	STATE_TEST
} state_t;

state_t current_state = STATE_STEPS;
state_t prev_state = STATE_STEPS;
static uint32_t fsmTaskNextRun = 0;

bool joystick_release = true;

void display_fsm_task_init(void)
{
	ssd1306_Init();
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("== STEP COUNTER ==", Font_7x10, White);
}

void update_fsm_display(state_t state) {
	// Set up the screen
	ssd1306_SetCursor(0, 13);

	// Call the function associated with this state
	switch(state) {
		case STATE_STEPS:
			steps_state_task_execute();
			break;
		case STATE_DISTANCE:
			distance_state_task_execute();
			break;
		case STATE_GOAL:
			goal_state_task_execute();
			break;
		case STATE_MODIFY_GOAL:
			modify_state_task_execute();
			break;
		case STATE_TEST:
			//ssd1306_WriteString("Test Mode       ", Font_7x10, White);
			test_state_task_execute();
			break;
	}

	ssd1306_UpdateScreen();
}

void display_fsm_task_execute(void) {
	// Task to be called by the scheduler, to move between FSM states

	// Pull flags from the joystick and modules
	// This is done regardless of whether fsmTaskNextRun has elapsed, as the
	// flags must be cleared at the same rate this task is executed at.
	struct joystick_position_flags joystick_position = get_joystick_flags();
	buttonState_t joystickButtonState = buttons_checkButton(JOYSTICK);
	buttonState_t SW2ButtonState = buttons_checkButton(DOWN);

	// Don't do anything if the last input was recent
	if (HAL_GetTick() < fsmTaskNextRun) return;

	// Implement state machine
	switch (current_state) {
		case STATE_STEPS:
			// Main state transitions
			if (joystick_position.left) current_state = STATE_DISTANCE;
			else if (joystick_position.right) current_state = STATE_GOAL;
			else if (SW2ButtonState == DOUBLE) current_state = STATE_TEST;

			// Unit switch transition
			if (joystick_position.up) {
				toggle_step_unit();
				// Although not a state change, we should wait before accepting
				// another input.
				fsmTaskNextRun = HAL_GetTick() + STATE_CHANGE_DELAY;
			}
			break;

		case STATE_DISTANCE:
			// Main state transitions
			if (joystick_position.left) current_state = STATE_GOAL;
			else if (joystick_position.right) current_state = STATE_STEPS;
			else if (SW2ButtonState == DOUBLE) current_state = STATE_TEST;

			// Unit switch transition
			if (joystick_position.up) {
				toggle_distance_unit();
				// Although not a state change, we should wait before accepting
				// another input.
				fsmTaskNextRun = HAL_GetTick() + STATE_CHANGE_DELAY;
			}
			break;

		case STATE_GOAL:
			if (joystickButtonState == HELD) current_state = STATE_MODIFY_GOAL;
			else if (joystick_position.left) current_state = STATE_STEPS;
			else if (joystick_position.right) current_state = STATE_DISTANCE;
			else if (SW2ButtonState == DOUBLE) current_state = STATE_TEST;
			break;

		case STATE_MODIFY_GOAL:
			if (joystickButtonState == HELD){
				current_state = STATE_GOAL;
				update_step_goal();
			} else if (joystickButtonState == PUSHED) current_state = STATE_GOAL;
			else if (SW2ButtonState == DOUBLE) current_state = STATE_TEST;
			break;

		case STATE_TEST:
			if (SW2ButtonState == DOUBLE) current_state = STATE_STEPS;
			break;
	}

	if (current_state != prev_state) {
		// If the state has changed, block changes for STATE_CHANGE_DELAY, and raise
		// the display update flag.
		fsmTaskNextRun = HAL_GetTick() + STATE_CHANGE_DELAY;
		prev_state = current_state;
	}

	// Call the display function associated with this state
	update_fsm_display(current_state);

}

