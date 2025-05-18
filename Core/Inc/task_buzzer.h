/*
 * task_buzzer.h
 *
 * Task to turn the buzzer on when the step goal is reached.
 *
 *  Created on: Apr 22, 2025
 *      Authors: C. Varney, A. Walker
 */

#ifndef TASK_BUZZER_H
#define TASK_BUZZER_H

#include <stdbool.h>
#include <stdint.h>
#include "buzzer.h"
#include "steps.h"

void task_buzzer_initTask(void);
void task_buzzer_executeTask(void);

#endif // TASK_BUZZER_H
