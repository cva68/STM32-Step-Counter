/*
 * state_test.g
 *
 * Functionality for the test mode of the step counter, allowing modification of the
 * current step count.
 *
 *  Created on: Apr 20, 2025
 *      Authors: C. Varney, A. Walker
 */

#ifndef STATE_TASK_TEST_H
#define STATE_TASK_TEST_H

#include <stdbool.h>
#include <stdio.h>
#include "steps.h"
#include "joystick.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"

void state_test_executeTask(void);

#endif // STATE_TASK_TEST_H
