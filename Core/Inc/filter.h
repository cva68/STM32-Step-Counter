/*
 * filter.h
 *
 * Each axisProperties_t has an associated filter_t, which is managed by the functions
 * of this module. Implements a basic circular buffer, of which the mean is extracted
 * from (FIR filter).
 *
 *  Created on: May 5, 2025
 *      Authors: C. Varney, A. Walker
 */

#ifndef FILTER_H_
#define FILTER_H_
#define NUM_TAPS 8  // Number of taps

#include <stdint.h>

typedef struct {
    int16_t buffer[NUM_TAPS];
    uint8_t index;
} Filter_t;

// Initializes the filter (zeros buffer and index)
void filter_init(Filter_t* filter);

// Takes in a new reading, and returns the filtered reading after
// said new reading is added to the buffer.
int16_t filter_apply(Filter_t* filter, int16_t input);

#endif /* FILTER_H_ */
