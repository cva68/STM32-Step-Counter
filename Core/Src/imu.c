/*
 * imu.c
 *
 *  Created on: May 5, 2025
 *      Author: awa158
 */
#include "imu.h"
#include "imu_lsm6ds.h"

#define X_OFFSET -740
#define Y_OFFSET -1555
#define Z_OFFSET 310
#define X_SCALE  976 // * 10 ^ -3
#define Y_SCALE  945 // * 10 ^ -3
#define Z_SCALE  966 // * 10 ^ -3
#define DIVIDER 1000

void imu_init(void){
	// Enable accelerometer with high performance
	imu_lsm6ds_write_byte(CTRL1_XL, CTRL1_XL_HIGH_PERFORMANCE);
}

int16_t get_x_acc(void) {
    uint8_t acc_x_low = imu_lsm6ds_read_byte(OUTX_L_XL); // Low byte
    uint8_t acc_x_high = imu_lsm6ds_read_byte(OUTX_H_XL); // High byte

    int32_t acc_x = (int16_t)((uint16_t)acc_x_high << 8) | acc_x_low;
    acc_x -= X_OFFSET;
    acc_x *= X_SCALE;
    acc_x /= DIVIDER;

    return (int16_t) acc_x;
}

int16_t get_y_acc(void) {
    uint8_t acc_y_low = imu_lsm6ds_read_byte(OUTY_L_XL); // Low byte
    uint8_t acc_y_high = imu_lsm6ds_read_byte(OUTY_H_XL); // High byte

    int32_t acc_y = (int16_t)((uint16_t)acc_y_high << 8) | acc_y_low;
    acc_y -= Y_OFFSET;
    acc_y *= Y_SCALE;
    acc_y /= DIVIDER;

    return (int16_t) acc_y;
}

int16_t get_z_acc(void) {
    uint8_t acc_z_low = imu_lsm6ds_read_byte(OUTZ_L_XL); // Low byte
    uint8_t acc_z_high = imu_lsm6ds_read_byte(OUTZ_H_XL); // High byte

    int32_t acc_z = (int16_t)((uint16_t)acc_z_high << 8) | acc_z_low;
    acc_z -= Z_OFFSET;
    acc_z *= Z_SCALE;
    acc_z /= DIVIDER;

    return (int16_t) acc_z;
}
