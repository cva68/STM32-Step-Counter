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

static bool update_display = false;
bool joystick_release = true;


void fsm_state_entry(state_t state) {
	// Set up the screen

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
			//test_state_task_execute();
			break;
	}
}

void fsm_task_execute(void) {
	// Task to be called by the scheduler, to move between FSM states

	// Don't do anything if the last input was recent
	if (HAL_GetTick() < fsmTaskNextRun) return;

	// Pull flags from the joystick module
	struct joystick_position_flags joystick_position = get_joystick_flags();

	// Implement state machine
	switch (current_state) {
		case STATE_STEPS:
			// Main state transitions
			if (joystick_position.left) current_state = STATE_DISTANCE;
			else if (joystick_position.right) current_state = STATE_GOAL;

			// Unit switch transition
			if (joystick_position.up) {
				toggle_step_unit();
				update_display = true;
			}
			break;

		case STATE_DISTANCE:
			// Main state transitions
			if (joystick_position.left) current_state = STATE_GOAL;
			else if (joystick_position.right) current_state = STATE_STEPS;

			// Unit switch transition
			if (joystick_position.up) {
				toggle_distance_unit();
				update_display = true;
			}
			break;

		case STATE_GOAL:
//			if (buttons_checkButton(JOYSTICK) == RELEASED){
//				joystick_release = true;
//			}
//			if (buttons_isHeld(JOYSTICK) && buttons_checkButton(JOYSTICK) == RELEASED) { // joystick long press
//				current_state = STATE_MODIFY_GOAL;
//				buttons_resetHeld(JOYSTICK);
//				joystick_release = false;
//			}
			// Main state transitions
			if (joystick_position.left) current_state = STATE_STEPS;
			else if (joystick_position.right) current_state = STATE_DISTANCE;
			break;

		case STATE_MODIFY_GOAL:
			// joystick long press and joystick short press
			update_display = true;
//			if (buttons_checkButton(JOYSTICK) == RELEASED){
//				if (joystick_release == true) {
//					current_state = STATE_GOAL;
//					joystick_release = false;
//				}
//				joystick_release = true;
//			}
//
//			 if (buttons_isHeld(JOYSTICK) && joystick_release == true) {
//				 update_step_goal();
//				current_state = STATE_GOAL;
//				joystick_release = false;
//
//			}
//			break;

		case STATE_TEST:
			// double press of sw2
			break;
	}


	if (current_state != prev_state || update_display) {
		// Reset the display before changing state
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("== STEP COUNTER ==", Font_7x10, White);
		ssd1306_SetCursor(0, 13);
		ssd1306_WriteString("                  ", Font_7x10, White); // Clear previous text
		ssd1306_SetCursor(0, 13);

		// Change state
		fsmTaskNextRun = HAL_GetTick() + STATE_CHANGE_DELAY;
		fsm_state_entry(current_state);
		prev_state = current_state;
		update_display = false;
	}
}

