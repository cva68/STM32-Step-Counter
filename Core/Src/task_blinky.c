#include "task_blinky.h"
#include "gpio.h"

void blinky_task_execute(void) {
	// Toggle LD1
	HAL_GPIO_TogglePin(NUCLEO_LD1_GPIO_Port, NUCLEO_LD1_Pin);
}
