/*
 * task_imu.c
 *
 *  Created on: May 5, 2025
 *      Author: awa158
 */

#include "task_imu.h"
#include "imu.h"
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>


void imu_task_init(void){
	imu_init();
}

void imu_task_execute(void) {
	int16_t z_acc = get_z_acc();
	char serial[14];
	int len = snprintf(serial, sizeof(serial), "%d\r\n", z_acc);
	HAL_UART_Transmit(&huart2, (int8_t*)serial, len, 10000);
}
