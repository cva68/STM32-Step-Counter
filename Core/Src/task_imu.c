/*
 * task_imu.c
 *
 *  Created on: May 5, 2025
 *      Author: awa158
 */

#include "task_imu.h"
#include "imu.h"
#include "usart.h"
#include "state_task_count.h"
#include <stdio.h>
#include <stdlib.h>

#define STEP_THRESHOLD 310000000
#define HYSTERESIS_LOWER 269000000
#define COOLDOWN_TICKS 20

static uint8_t cooldown = 0;

void imu_task_init(void){
	imu_init();
}

void imu_task_execute(void) {
	static bool hysteresis = false;
	uint32_t mag = get_magnitude();
	char serial[14];
	int len = snprintf(serial, sizeof(serial), "%d\r\n", mag);
	HAL_UART_Transmit(&huart2, (int8_t*)serial, len, 10000);


    if (cooldown > 0) {
        cooldown--;
        return;
    }

	if (mag < HYSTERESIS_LOWER) {
		hysteresis = false;
	}
	if (mag > STEP_THRESHOLD && !hysteresis) {
		hysteresis = true;
		increment_steps(1);
		cooldown = COOLDOWN_TICKS;  // Prevent double-counting
	}
}
