/*
 * filter.c
 *
 *  Created on: May 5, 2025
 *      Author: cva68
 */

#include "filter.h"
#include <stdio.h>
#include <stdint.h>
#define N 8 // Number of samples in the circular buffer

void filter_init(Filter_t* filter) {
    for (int i = 0; i < N; i++) {
        filter->buffer[i] = 0;
    }
    filter->index = 0;
}

int16_t filter_apply(Filter_t* filter, int16_t input) {
    filter->buffer[filter->index] = input;
    filter->index = (filter->index + 1) % N;

    int32_t sum = 0;
    for (int i = 0; i < N; i++) {
        sum += filter->buffer[i];  // All coefficients are 1
    }

    return sum / N; //Change so that when there are empty values N is equal to the amount of filled spaces
}
