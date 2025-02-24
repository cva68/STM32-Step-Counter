#include "app.h"
#include "gpio.h"
#include "rgb.h"

void app_main(void) {
	while(1){
		HAL_Delay(200);
		HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);

		rgb_colour_on(RGB_RED);
		rgb_colour_on(RGB_GREEN);
		rgb_colour_on(RGB_BLUE);

		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11)) {
			rgb_led_on(RGB_UP);
		} else {
			rgb_led_off(RGB_UP);
		}

		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1)) {
			rgb_led_on(RGB_DOWN);
		} else {
			rgb_led_off(RGB_DOWN);
		}

		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10)) {
			rgb_led_on(RGB_LEFT);
		} else {
			rgb_led_off(RGB_LEFT);
		}

		if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)) {
			rgb_led_off(RGB_RIGHT);
		} else {
			rgb_led_on(RGB_RIGHT);
		}
	}
}

//Wip
void connect_led_to_switch(rgb_led_t led, rgb_colour_t colour){
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11)) {
		rgb_led_on(RGB_LEFT);
		rgb_colour_on(RGB_RED);
	} else {
		rgb_led_off(RGB_LEFT);
		rgb_colour_off(RGB_RED);
	}
}
