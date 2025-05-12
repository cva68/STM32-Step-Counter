/*
 * imu.c
 *
 *  Created on: May 5, 2025
 *      Author: awa158
 */
#include "imu.h"
#include "imu_lsm6ds.h"

void imu_init(void){
	// Enable accelerometer with high performance
	imu_lsm6ds_write_byte(CTRL1_XL, CTRL1_XL_HIGH_PERFORMANCE);
}

int16_t get_x_acc(void) {
    uint8_t acc_x_low = imu_lsm6ds_read_byte(OUTX_L_XL); // Low byte
    uint8_t acc_x_high = imu_lsm6ds_read_byte(OUTX_H_XL); // High byte

    int16_t acc_x = ((uint16_t)acc_x_high << 8) | acc_x_low;

    return acc_x;
}

int16_t get_y_acc(void) {
    uint8_t acc_y_low = imu_lsm6ds_read_byte(OUTY_L_XL); // Low byte
    uint8_t acc_y_high = imu_lsm6ds_read_byte(OUTY_H_XL); // High byte

    int16_t acc_y = ((uint16_t)acc_y_high << 8) | acc_y_low;

    return acc_y;
}

int16_t get_z_acc(void) {
    uint8_t acc_z_low = imu_lsm6ds_read_byte(OUTZ_L_XL); // Low byte
    uint8_t acc_z_high = imu_lsm6ds_read_byte(OUTZ_H_XL); // High byte

    int16_t acc_z = ((uint16_t)acc_z_high << 8) | acc_z_low;

    return acc_z;
}
