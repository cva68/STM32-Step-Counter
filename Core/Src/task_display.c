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

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void display_task_init(void) {
	ssd1306_Init();
	ssd1306_SetCursor(0, 0);
}

void display_task_execute(void) {
	// Fetch coordinate strings
	ssd1306_UpdateScreen();
}
