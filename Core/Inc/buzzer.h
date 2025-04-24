/*
 * buzzer.h
 *
 *  Created on: Apr 22, 2025
 *      Author: awa158
 */

#include <stdint.h>
#include "gpio.h"

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_


void buzzer_init(void);

void set_buzzer(int32_t duty_cycle);

#endif /* INC_BUZZER_H_ */
