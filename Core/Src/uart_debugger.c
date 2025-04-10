/*
 * uart_debugger.c
 *
 *  Created on: Mar 16, 2025
 *      Author: cva68
 */

#include "uart_debugger.h"
#include "usart.h"

void send_debug_message(char *message) {
	// Send a message over UART
	//HAL_UART_Transmit(&huart2, message, 14, 10000);
}
