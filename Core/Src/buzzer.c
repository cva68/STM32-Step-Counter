/*
 * buzzer.c
 *
 *  Created on: Apr 22, 2025
 *      Author: awa158
 */
#include "gpio.h"
#include <stdint.h>
#include "buzzer.h"
#include "pwm.h"

void buzzer_init(void){
	HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
}

void set_buzzer(int32_t duty_cycle){
	__HAL_TIM_SET_COMPARE(&htim16, TIM_CHANNEL_1, duty_cycle);
}
