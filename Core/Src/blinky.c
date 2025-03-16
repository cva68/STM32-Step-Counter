/*
 * blinky.c
 *
 *  Created on: Mar 16, 2025
 *      Author: cva68
 */

#include "blinky.h"
#include "gpio.h"

void toggle_led(void) {
	HAL_GPIO_TogglePin(NUCLEO_LD1_GPIO_Port, NUCLEO_LD1_Pin);
}
