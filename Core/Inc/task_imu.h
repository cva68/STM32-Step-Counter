/*
 * task_imu.c
 *
 * Task to read the filtered magnitude from the IMU, and increment the step counter if it exceeds
 * a threshold. Uses hysteresis, as well as a limit on how much time must elapse between steps. 
 * Also aims to reject input when the device is sat on a flat surface, by analysing the Z acceleration.
 *
 *  Created on: May 5, 2025
 *      Authors: C. Varney, A. Walker
 */

#ifndef TASK_IMU_H_
#define TASK_IMU_H_

void task_imu_initTask(void);
void task_imu_executeTask(void);

#endif /* INC_TASK_IMU_H_ */
