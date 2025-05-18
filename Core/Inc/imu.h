/*
 * imu.h
 *
 *  Created on: May 5, 2025
 *      Author: awa158
 */

#ifndef INC_IMU_H_
#define INC_IMU_H_

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
int16_t get_raw_acceleration(axis_t axis);
int16_t get_filtered_acceleration(axis_t axis);
uint32_t get_magnitude(void);

#endif /* INC_IMU_H_ */
