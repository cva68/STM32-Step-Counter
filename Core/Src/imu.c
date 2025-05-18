/*
 * imu.c
 *
 * IMU Abstraction. Allows getting raw or filtered acceleration in each direction axis_t (X, Y or Z).
 * Each axis has an associated Filter_t, and every call to imu_getFilteredAcceleration will populate
 * the circular buffer of this filter.
 *
 *  Created on: May 5, 2025
 *  	Authors: C. Varney, A. Walker
 */

#include "imu.h"
#include "imu_lsm6ds.h"
#include "filter.h"

// X, Y, Z
#define NUM_AXIS 3

// Because axisProperties_t.scale would need to be a float, we
// instead store it as an integer, then divide by SCALE_DIVIDER.
#define SCALE_DIVIDER 1000 

// Create new FIR filters for each axis
Filter_t xFilter;
Filter_t yFilter;
Filter_t zFilter;

// Measurements were taken to find the zero-offsets and scales required to
// ensure acceleration measurements in the X, Y and Z directions are all consistent,
// w.r.t 0 and 1G.
axisProperties_t axis_properties[NUM_AXIS] =
{
		// X direction
		[X] = {
			.offset = -740,
            .scale = 976,  // * 10 ^ -3
            .low_byte = OUTX_L_XL,
            .high_byte = OUTX_H_XL,
			.filter = &xFilter
		},

		// Y direction
		[Y] = {
			.offset = -1555,
            .scale = 945,  // * 10 ^ -3
            .low_byte = OUTY_L_XL,
            .high_byte = OUTY_H_XL,
			.filter = &yFilter
		},

	    // Z direction
		[Z] =
		{
			.offset = 310,
            .scale = 966,  // * 10 ^ -3
            .low_byte = OUTZ_L_XL,
            .high_byte = OUTZ_H_XL,
			.filter = &zFilter
		}
};

void imu_init(void)
{
	// Enable accelerometer
	imu_lsm6ds_write_byte(CTRL1_XL, CTRL1_XL_HIGH_PERFORMANCE);

    // Set up filters for each accelerometer axis
    for (int i = 0; i < NUM_AXIS; i++)
	{
		filter_init(axis_properties[i].filter);
	}
}

int16_t imu_getRawAcceleration(axis_t axis)
{
	// Get unfiltered acceleration value of a given axis
    uint8_t acc_low = imu_lsm6ds_read_byte(axis_properties[axis].low_byte); // Low byte
    uint8_t acc_high = imu_lsm6ds_read_byte(axis_properties[axis].high_byte); // High byte

    int32_t acceleration = (int16_t)((uint16_t)acc_high << 8) | acc_low;
    acceleration -= axis_properties[axis].offset;
    acceleration *= axis_properties[axis].scale;
    acceleration /= SCALE_DIVIDER;

    return (int16_t) acceleration;
}

int16_t imu_getFilteredAcceleration(axis_t axis)
{
	// Get filtered acceleration value of a given axis, which will simulatenously
	// shift the current acceleration value into the filter circular buffer.
	int16_t acc = imu_getRawAcceleration(axis);
	int16_t acc_filtered = filter_apply(axis_properties[axis].filter, acc);
	return acc_filtered;
}

uint32_t imu_getMagnitude(void) {
	// Get the acceleration magnitude squared (as to avoid sqrts)
    int32_t acceleration_magnitude  = 0;
    int16_t this_acceleration;

    for (int i = 0; i < NUM_AXIS; i++)
	{
		this_acceleration = imu_getFilteredAcceleration(i);
        acceleration_magnitude += this_acceleration * this_acceleration;
	}

	return acceleration_magnitude;
}
