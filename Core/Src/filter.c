/*
 * filter.c
 *
 *  Created on: May 5, 2025
 *      Author: cva68
 */

#include <stdio.h>
#include <stdint.h>
#define N 4 // Number of samples in the circular buffer

uint16_t coeffs[N] =  {1, 1, 1, 1};

// FIR Filter function
uint16_t fir_filter(uint16_t input) {
	static struct CircBuffer_t buffer;
	uint16_t output = 0;
	buffer.buffer[buffer.index] = input;

	// Compute FIR filter output
	for (count_t i = 0; i < N; i ++) {
		output += coeffs[i] * buffer.buffer[(buffer.index - i + N) % N];
	}

	buffer.index = (buffer.index + 1) % N;
	return output / N;
}
