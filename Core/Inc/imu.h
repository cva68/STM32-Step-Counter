/*
 * imu.h
 *
 * IMU Abstraction. Allows getting raw or filtered acceleration in each direction axis_t (X, Y or Z).
 * Each axis has an associated Filter_t, and every call to imu_getFilteredAcceleration will populate
 * the circular buffer of this filter.
 *
 *  Created on: May 5, 2025
 *      Authors: C. Varney, A. Walker
 */

#ifndef IMU_H
#define IMU_H

#include <stdint.h>
#include "imu.h"
#include "filter.h"
#include "imu_lsm6ds.h"

typedef enum axisNames {X = 0, Y, Z} axis_t;

// Storing offsets and scales in a struct allows
// for iteration through dimensions.
typedef struct {
    const int16_t offset;
    const uint16_t scale;
    const imu_register_t low_byte;
    const imu_register_t high_byte;
    Filter_t* filter;
} axisProperties_t;

void imu_init(void);
int16_t imu_getRawAcceleration(axis_t axis);
int16_t imu_getFilteredAcceleration(axis_t axis);
uint32_t imu_getMagnitude(void);

#endif // IMU_H
