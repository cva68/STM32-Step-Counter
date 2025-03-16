/*
 * task_uart.h
 *
 *  Created on: Mar 16, 2025
 *      Author: cva68
 */

#ifndef INC_TASK_UART_H_
#define INC_TASK_UART_H_

#include "usart.h"
#include "gpio.h"

#include <stdbool.h>

void uart_task_execute(bool SW2_state);


#endif /* INC_TASK_UART_H_ */
