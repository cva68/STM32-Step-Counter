/*
 * position.c
 *
 *  Created on: May 12, 2025
 *      Author: awa158
 */

#include "task_imu.h"
#include "imu.h"
#include "usart.h"
#include "filter.h"
#include <stdio.h>
#include <stdlib.h>

Filter_t x_filter;
Filter_t y_filter;
Filter_t z_filter;

void position_init(void){
	imu_init();
	filter_init(&x_filter);
	filter_init(&y_filter);
	filter_init(&z_filter);
}

int16_t get_filtered_x(void) {
	int16_t x_acc = get_x_acc();
	int16_t x_acc_filtered = filter_apply(&x_filter, x_acc);
	return x_acc_filtered;
}

int16_t get_filtered_y(void) {
	int16_t y_acc = get_y_acc();
	int16_t y_acc_filtered = filter_apply(&y_filter, y_acc);
	return y_acc_filtered;
}

int16_t get_filtered_z(void) {
	int16_t z_acc = get_z_acc();
	int16_t z_acc_filtered = filter_apply(&z_filter, z_acc);
	return z_acc_filtered;
}

uint32_t get_mag(void) {
	int16_t x_acc = get_filtered_x();
	int16_t y_acc = get_filtered_y();
	int16_t z_acc = get_filtered_z();

	int32_t acc_mag = (x_acc * x_acc) + (y_acc * y_acc) + (z_acc * z_acc);
	return acc_mag;
}
