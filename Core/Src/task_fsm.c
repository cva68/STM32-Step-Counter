/*
 * task_fsm.c
 *
 *  Created on: Apr 9, 2025
 *      Author: connor
 */

#include "joystick.h"
#include "buttons.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

#define STATE_CHANGE_DELAY 500 // Ticks

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


void steps_state_task_execute(void)
{
	ssd1306_WriteString("steps", Font_7x10, White);
}

void distance_state_task_execute(void)
{
	ssd1306_WriteString("dist", Font_7x10, White);
}

void goal_state_task_execute(void)
{
	ssd1306_WriteString("goal", Font_7x10, White);
}

void modify_state_task_execute(void)
{
	ssd1306_WriteString("mod", Font_7x10, White);
}

void test_state_task_execute(void)
{
	ssd1306_WriteString("test", Font_7x10, White);
}

void fsm_task_execute(void) {
	if (HAL_GetTick() < fsmTaskNextRun) return;

	struct joystick_position_flags joystick_position = get_joystick_flags();

	switch (current_state) {
		case STATE_STEPS:
			if (joystick_position.left) current_state = STATE_DISTANCE;
			else if (joystick_position.right) current_state = STATE_GOAL;
			break;

		case STATE_DISTANCE:
			if (joystick_position.left) current_state = STATE_GOAL;
			else if (joystick_position.right) current_state = STATE_STEPS;
			break;

		case STATE_GOAL:
			if (joystick_position.long_press || joystick_position.short_press)
				current_state = STATE_MODIFY_GOAL;
			else if (joystick_position.left) current_state = STATE_STEPS;
			else if (joystick_position.right) current_state = STATE_DISTANCE;
			break;

		case STATE_MODIFY_GOAL:
			if (joystick_position.long_press || joystick_position.short_press)
				current_state = STATE_GOAL;
			break;

		case STATE_TEST:
			break;
	}

	if (current_state != prev_state) {
		fsmTaskNextRun = HAL_GetTick() + STATE_CHANGE_DELAY;
		// Display on OLED
		ssd1306_SetCursor(0, 0);
		ssd1306_WriteString("                    ", Font_7x10, White); // Clear previous text
		ssd1306_SetCursor(0, 0);
		fsm_state_entry(current_state);
		prev_state = current_state;
	}
}

void fsm_state_entry(state_t state) {
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
			test_state_task_execute();
			break;
	}
}

