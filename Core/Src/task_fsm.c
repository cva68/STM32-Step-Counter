/*
 * task_display_fsm.c
 *
 * Task to switch between FSM states based on joystick / button inputs.
 *
 *  Created on: Apr 9, 2025
 *      Authors: C. Varney, A. Walker
 */

#include <stdio.h>
#include <stdbool.h>

#include "task_fsm.h"
#include "joystick.h"
#include "buttons.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

#include "state_count.h"
#include "state_distance.h"
#include "state_goal.h"
#include "state_test.h"

// Minimum time to stay in each state
#define STATE_CHANGE_DELAY 400 // Ticks

state_t current_state = STATE_STEPS;
state_t prev_state = STATE_STEPS;
static uint32_t fsmTaskNextRun = 0;

void task_fsm_initTask(void)
{
	ssd1306_Init();
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("== STEP COUNTER ==", Font_7x10, White);
}

void task_fsm_updateDisplay(state_t state) {
	// Set up the screen
	ssd1306_SetCursor(0, 13);

	// Call the function associated with this state
	switch(state) {
		case STATE_STEPS:
			state_count_executeTask();
			break;
		case STATE_DISTANCE:
			state_distance_executeTask();
			break;
		case STATE_GOAL:
			state_goal_executeDisplayTask();
			break;
		case STATE_MODIFY_GOAL:
			state_goal_executeModifyTask();
			break;
		case STATE_TEST:
			//ssd1306_WriteString("Test Mode       ", Font_7x10, White);
			state_test_executeTask();
			break;
	}
	ssd1306_UpdateScreen();
}

void task_fsm_taskExecute(void) {
	// Task to be called by the scheduler, to move between FSM states

	// Pull flags from the joystick and modules
	// This is done regardless of whether fsmTaskNextRun has elapsed, as the
	// flags must be cleared at the same rate this task is executed at.
	struct joystick_position_flags joystick_position = joystick_getFlags();
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
				state_count_toggleUnit();
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
				state_distance_toggleUnit();
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
				state_goal_updateGoal();
			} else if (joystickButtonState == PUSHED) current_state = STATE_GOAL;
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
	task_fsm_updateDisplay(current_state);
} //task_fsm_taskExecute
