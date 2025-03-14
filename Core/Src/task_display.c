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

	// Convert raw values to percentage
	int8_t x_percentage = (((int16_t)raw_adc[1] - 2047) *100) / 2047;
	int8_t y_percentage = (((int16_t)raw_adc[0] - 2047) *100) / 2047;

	const char *x_direction;
	const char *y_direction;

	if (x_percentage > 10) {
	    x_direction = "Left";
	} else if (x_percentage < -10) {
	    x_direction = "Right";
	} else {
	    x_direction = "Rest";
	}

	if (y_percentage > 10) {
	    y_direction = "Down";
	} else if (y_percentage < -10) {
	    y_direction = "Up";
	} else {
	    y_direction = "Rest";
	}

	// Create formatted strings
	char result[14] = "";
	snprintf(result, sizeof(result), "%u,%u\r\n", raw_adc[0], raw_adc[1]);

	char x_string[14] = "";
	char y_string[14] = "";

	if(strcmp(y_direction, "Rest") == 0){
		snprintf(y_string, sizeof(y_string), "%s", y_direction);
	}else{
		snprintf(y_string, sizeof(y_string), "%s,%u%%\r\n", y_direction, abs(y_percentage));
	}

	if(strcmp(x_direction, "Rest") == 0){
		snprintf(x_string, sizeof(x_string), "%s", x_direction);
	}else{
		snprintf(x_string, sizeof(x_string), "%s,%u%%\r\n", x_direction, abs(x_percentage));
	}


	// Display on OLED
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("                    ", Font_7x10, White); // Clear previous text
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString(result, Font_7x10, White);
	ssd1306_SetCursor(0, 13);
	ssd1306_WriteString("                    ", Font_7x10, White); // Clear previous text
	ssd1306_SetCursor(0, 13);
	ssd1306_WriteString(x_string, Font_7x10, White);
	ssd1306_SetCursor(0, 26);
	ssd1306_WriteString("                    ", Font_7x10, White); // Clear previous text
	ssd1306_SetCursor(0, 26);
	ssd1306_WriteString(y_string, Font_7x10, White);
	ssd1306_UpdateScreen();
	HAL_UART_Transmit(&huart2, &result, 12, 10000);
}
