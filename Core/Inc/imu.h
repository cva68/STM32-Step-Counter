/*
 * imu.h
 *
 *  Created on: May 5, 2025
 *      Author: awa158
 */

#ifndef INC_IMU_H_
#define INC_IMU_H_

#include <stdint.h>

void imu_init(void);
int16_t get_x_acc(void);
int16_t get_y_acc(void);
int16_t get_z_acc(void);

#endif /* INC_IMU_H_ */
