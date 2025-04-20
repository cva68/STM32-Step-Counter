/*
 * state_task_test.h
 *
 * Contains functionality for the test state of the FSM
 *
 *  Created on: Apr 20, 2025
 *      Author: cva68
 */

#ifndef STATE_TASK_TEST_H
#define STATE_TASK_TEST_H

#include <stdbool.h>
#include <stdio.h>
#include "state_task_count.h" // For getting current number of steps
#include "state_task_goal.h" // For getting current goal
#include "joystick.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

void test_state_task_execute(void);

#endif // STATE_TASK_TEST_H
