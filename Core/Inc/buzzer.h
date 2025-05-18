/*
 * buzzer.h
 *
 * Basic abstraction for the RCAP buzzer, providing ability to turn it on at a
 * set duty cycle.
 * 
 *  Created on: Apr 22, 2025
 *      Authors: C. Varney, A. Walker
 */

#include <stdint.h>
#include "gpio.h"

#ifndef BUZZER_H
#define BUZZER_H


void buzzer_init(void);
void buzzer_set(int32_t duty_cycle);

#endif // BUZZER_H
