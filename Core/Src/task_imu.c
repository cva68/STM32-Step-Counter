/*
 * task_imu.c
 *
 * Task to read the filtered magnitude from the IMU, and increment the step counter if it exceeds
 * a threshold. Uses hysteresis, as well as a limit on how much time must elapse between steps. 
 * Also aims to reject input when the device is sat on a flat surface, by analysing the Z acceleration.
 *
 *  Created on: May 5, 2025
 *      Authors: C. Varney, A. Walker
 */

#include <stdio.h>
#include <stdlib.h>

#include "task_imu.h"
#include "imu.h"
#include "usart.h"
#include "state_count.h"


// Upper and lower bound for hysteresis range
#define HYSTERISIS_UPPER 310000000
#define HYSTERESIS_LOWER 269000000

// Range around Z=1G to reject step input (i.e. try avoid
// counting steps when the device is sitting on a flat surface
#define Z_REJECTION_MIN 15600
#define Z_REJECTION_MAX 16800

// Minimum time between registering steps
#define COOLDOWN_TICKS 20 // ticks

static uint8_t cooldown = 0;

void task_imu_initTask(void){
	imu_init();
}

void task_imu_executeTask(void) {
	static bool hysteresis = false;
	uint32_t mag = imu_getMagnitude();
	uint16_t z_acceleration = imu_getFilteredAcceleration(Z);

	// If we're reasonably certain the device is sitting on a level surface,
	// don't count steps. 
	if (z_acceleration < Z_REJECTION_MAX && z_acceleration > Z_REJECTION_MIN) {
		return;
	}

	// If the last step was recent, don't count another
    if (cooldown > 0) {
        cooldown--;
        return;
    }

    // If we're below the bottom hysteresis threshold, drop the flag
    // that prevents new steps being registered
	if (mag < HYSTERESIS_LOWER) {
		hysteresis = false;
	}

	// If the hysteresis flag isn't raised and the magnitude exceeds the
	// upper hysteresis threshold, increment the step count
	if (mag > HYSTERISIS_UPPER && !hysteresis) {
		hysteresis = true;
		steps_incrementSteps(1);
		cooldown = COOLDOWN_TICKS;  // Prevent double-counting
	}
}
