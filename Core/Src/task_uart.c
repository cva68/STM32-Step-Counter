/*
 * task_display.c
 *
 *  Created on: Mar 10, 2025
 *      Author: awa158
 */
#include "task_uart.h"
#include "uart_debugger.h"
#include "joystick.h"

#include <stdbool.h>

void uart_task_execute(bool SW2_state) {
	// Transmit debug values, if SW2_state is 1
	if (SW2_state) {
		char *raw;
		raw = raw_adc_as_string();
		send_debug_message(raw);
	}
}
