/*
 * imu.c
 *
 *  Created on: May 5, 2025
 *      Author: awa158
 */
#include "imu.h"
#include "imu_lsm6ds.h"
#include "filter.h"

// X, Y, Z
#define NUM_AXIS 3

// Instead of storing large axisProperties_t.scale values,
// we store smaller integers then divide by this value.
#define SCALE_DIVIDER 1000 

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

void imu_init(void){
	// Enable accelerometer
	imu_lsm6ds_write_byte(CTRL1_XL, CTRL1_XL_HIGH_PERFORMANCE);

    // Set up filters for each accelerometer axis
    for (int i = 0; i < NUM_AXIS; i++)
	{
		filter_init(axis_properties[i].filter);
	}
}

int16_t get_raw_acceleration(axis_t axis)
{
    uint8_t acc_low = imu_lsm6ds_read_byte(axis_properties[axis].low_byte); // Low byte
    uint8_t acc_high = imu_lsm6ds_read_byte(axis_properties[axis].high_byte); // High byte

    int32_t acceleration = (int16_t)((uint16_t)acc_high << 8) | acc_low;
    acceleration -= axis_properties[axis].offset;
    acceleration *= axis_properties[axis].scale;
    acceleration /= SCALE_DIVIDER;

    return (int16_t) acceleration;
}

int16_t get_filtered_acceleration(axis_t axis)
{
	int16_t acc = get_raw_acceleration(axis);
	int16_t acc_filtered = filter_apply(axis_properties[axis].filter, acc);
	return acc_filtered;
}

uint32_t get_magnitude(void) {
    int32_t acceleration_magnitude  = 0;
    int16_t this_acceleration;

    for (int i = 0; i < NUM_AXIS; i++)
	{
		this_acceleration = get_filtered_acceleration(i);
        acceleration_magnitude += this_acceleration * this_acceleration;
	}

	return acceleration_magnitude;
}
