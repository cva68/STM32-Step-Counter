/*
 * filter.h
 *
 *  Created on: May 5, 2025
 *      Author: cva68
 */

#ifndef FILTER_H_
#define FILTER_H_

#define N 4

#include <stdint.h>


typedef struct {
	uint16_t current_values[N] = {0};
	uint8_t index = 0;
} CircBuffer_t;

uint16_t fir_filter(uint16_t input);

#endif /* INC_FILTER_H_ */
