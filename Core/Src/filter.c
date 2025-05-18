/*
 * filter.c
 *
 * Each axisProperties_t has an associated filter_t, which is managed by the functions
 * of this module. Implements a basic circular buffer, of which the mean is extracted
 * from (FIR filter).
 *
 *  Created on: May 5, 2025
 *      Authors: C. Varney, A. Walker
 */

#include "filter.h"
#include <stdio.h>
#include <stdint.h>

#define NUM_SAMPLES 8 // Number of samples in the circular buffer

// Initialise the struct
void filter_init(Filter_t* filter)
{
    for (int i = 0; i < NUM_SAMPLES; i++) {
        filter->buffer[i] = 0;
    }
    filter->index = 0;
}

// Takes in a new reading, and returns the filtered reading after
// said new reading is added to the buffer.
int16_t filter_apply(Filter_t* filter, int16_t input)
{
    // Add the new value at the current index, then move the index
    filter->buffer[filter->index] = input;
    filter->index = (filter->index + 1) % NUM_SAMPLES;

    // Calculate and return mean
    int32_t sum = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        sum += filter->buffer[i];  // All coefficients are 1
    }

    return sum / NUM_SAMPLES;
}
