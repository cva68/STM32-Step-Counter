/*
 * task_led.g
 *
 * Task to turn on LEDs as the step goal approaches completion. DS4 lights up gradually
 * with PWM from 0% to 25% completion, DS1-DS3 turn on for the remaining 25% increments.
 *
 *  Created on: May 12, 2025
 *      Authors: C. Varney, A. Walker
 */

#ifndef TASK_LED_H
#define TASK_LED_H

#include <stdint.h>
#include "gpio.h"
#include "pwm.h"
#include "steps.h"

void task_led_initTask(void);
void task_led_executeTask(void);


#endif // TASK_LED_H
