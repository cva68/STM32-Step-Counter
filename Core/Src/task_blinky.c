#include "task_blinky.h"
#include "blinky.h"

void blinky_task_execute(void) {
	// Toggle LD1
	toggle_led();
}
