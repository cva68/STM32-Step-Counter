/*
 * app.h
 *
 * Time-based scheduler for each step counter task, implementing an interrupt-driven kernel
 * with HAL_GetTick().
 * 
 * Modified from code provided by the University of Canterbury (ENCE361)
 *
 *  Created on: Mar 6, 2025
 *      Authors: C. Varney, A. Walker
 */

#ifndef APP_H
#define APP_H

#include <stdint.h>
#include "task_adc.h"
#include "gpio.h"
#include "task_buttons.h"
#include "task_joystick.h"
#include "task_fsm.h"
#include "task_buzzer.h"
#include "task_imu.h"

void app_main(void);
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin);

#endif // APP_H



