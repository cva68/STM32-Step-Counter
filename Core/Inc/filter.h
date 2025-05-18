/*
 * filter.h
 *
 *  Created on: May 5, 2025
 *      Author: cva68
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

// Applies the filter to a new input value
int16_t filter_apply(Filter_t* filter, int16_t input);

#endif /* FILTER_H_ */
