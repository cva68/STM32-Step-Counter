/*
 * task_display.c
 *
 *  Created on: Mar 10, 2025
 *      Author: awa158
 */
#include "task_display.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include "ssd1306_conf.h"
#include "joystick.h"
#include "usart.h"
#include "gpio.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void display_task_init(void) {
	ssd1306_Init();
	ssd1306_SetCursor(0, 0);
}

void display_task_execute(void) {
	uint16_t *raw_adc = get_raw_values();
	char result[14] = "";
	snprintf(result, 12, "%u,%u\r\n", raw_adc[0], raw_adc[1]);

	ssd1306_SetCursor(0,0);
	ssd1306_WriteString("                    ", Font_7x10, White);
	ssd1306_SetCursor(0,0);
	ssd1306_WriteString(result, Font_7x10, White);
	ssd1306_UpdateScreen();
	HAL_UART_Transmit(&huart2, &result, 12, 10000);
}
