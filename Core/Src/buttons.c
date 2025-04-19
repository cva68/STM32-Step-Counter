// *******************************************************
// 
// buttons.c
//
//
// Support for a set of FOUR specific buttons on the NUCLEO boards.
// ENCE361 sample code.
// The buttons are UP/DOWN/LEFT/RIGHT.
//
// Created by P.J. Bones, UC ECE
// Updated by Le Yang & F. Youssif, UC ECE.
// Last modified:  15/01/2025
// 
// *******************************************************

#include <stdint.h>
#include <stdbool.h>

#include "buttons.h"
#include "stm32c0xx_hal.h"

#define NUM_BUT_POLLS 3

#define HOLD_THRESHOLD_MS 500
#define RELEASE_THRESHOLD_MS 150

#define BUTTON_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/BUTTON_TASK_FREQUENCY)
#define JOYSTICK_TASK_PERIOD_TICKS (TICK_FREQUENCY_HZ/JOYSTICK_TASK_FREQUENCY)

// *******************************************************
// Typedefs
// *******************************************************
typedef struct
{
	// Constant config
	GPIO_TypeDef* const port;
	const uint16_t pin;
	const GPIO_PinState normalState;

	// Runtime properties
	GPIO_PinState pinState;
	buttonState_t buttonState;
	uint32_t lastChangeTicks;
	uint8_t newStateCount;
	bool hasChanged;
} buttonProperties_t;

// *******************************************************
// Globals to module
// *******************************************************
buttonProperties_t buttons[NUM_BUTTONS] =
{
		// UP button (SW1, PC11, active HIGH)
		[UP] = {
			.port = GPIOC,
			.pin = GPIO_PIN_11,
			.normalState = GPIO_PIN_RESET
		},
		// DOWN button (SW2, PC1, active HIGH)
		[DOWN] = {
			.port = GPIOC,
			.pin = GPIO_PIN_1,
			.normalState = GPIO_PIN_RESET
		},
	    // LEFT button (SW4, PC13, active LOW)
		[LEFT] =
		{
			.port = GPIOC,
			.pin = GPIO_PIN_13,
			.normalState = GPIO_PIN_SET
		},
		// RIGHT button (SW3, PC10, active HIGH)
		[RIGHT] =
		{
			.port = GPIOC,
			.pin = GPIO_PIN_10,
			.normalState = GPIO_PIN_RESET
		},
		// JOYSTICK button
		[JOYSTICK] =
		{
			.port = GPIOB,
			.pin = GPIO_PIN_1,
			.normalState = GPIO_PIN_RESET
		}

};

// *******************************************************
// buttons_init: Initialise the variables associated with the set of buttons.
void buttons_init (void)
{
	for (int i = 0; i < NUM_BUTTONS; i++)
	{
		buttons[i].pinState = buttons[i].normalState;
		buttons[i].newStateCount = 0;
		buttons[i].hasChanged = false;
	}
}

// *******************************************************
// buttons_update: Function designed to be called regularly. It polls all
// buttons once and updates variables associated with the buttons if
// necessary. It is efficient enough to be part of an ISR for e.g.,
// a SysTick interrupt.
// Debouncing algorithm: A finite state machine (FSM) is associated with each button.
// A state change can be declared only after NUM_BUT_POLLS consecutive polls have
// read the pin in the opposite condition, before the state changes and
// a flag is set. Set NUM_BUT_POLLS according to the polling rate.
void buttons_update (void)
{
	static uint8_t dutyCycle = 0;
	// Iterate through the buttons, updating button variables as required
	for (int i = 0; i < NUM_BUTTONS; i++)
	{
		// Read the pin value
		GPIO_PinState rawState = HAL_GPIO_ReadPin(buttons[i].port, buttons[i].pin);

		// If reading is different from last confirmed state, increment counter
        if (rawState != buttons[i].pinState)
        {
        	buttons[i].newStateCount++;

        	// If count exceeds poll count, confirm change of state
        	if (buttons[i].newStateCount >= NUM_BUT_POLLS)
        	{
        		buttons[i].pinState = rawState;
        		buttons[i].hasChanged = true;	// Reset by call to buttons_checkButton()
        		buttons[i].newStateCount = 0;
        	}
        }
        else
        {
        	buttons[i].newStateCount = 0;
        }

        // Button FSM
        switch (buttons[i].buttonState) {
        		case RELEASED:
        			// If the button has just been pushed, move to the first wait state
        			if (buttons[i].hasChanged && buttons[i].pinState != buttons[i].normalState){
        				buttons[i].buttonState = WAIT1;
        				buttons[i].lastChangeTicks = HAL_GetTick();
        				buttons[i].hasChanged = false;
        			}
        			break;

        		case WAIT1:
        			// If the button has been released, move to the second wait state
        			if (buttons[i].pinState == buttons[i].normalState){
        				buttons[i].buttonState = WAIT2;
        				buttons[i].lastChangeTicks = HAL_GetTick();
        				buttons[i].hasChanged = false;
        			}

        			// If we're waiting and the hold threshold is exceeded, can confirm the button is held.
        			else if (HAL_GetTick() > buttons[i].lastChangeTicks + HOLD_THRESHOLD_MS) {
        				buttons[i].buttonState = HELD;
        			}
        			break;

        		case WAIT2:
        			// If we're in the second wait state and we get another push, the button has been double clicked.
        			if (buttons[i].pinState != buttons[i].normalState) {
        				buttons[i].buttonState = DOUBLE;
        				buttons[i].hasChanged = false;
        			}

        			// If we're in the second wait state and we time out waiting for another click, the button has
        			// been single clicked.
        			else if (HAL_GetTick() > buttons[i].lastChangeTicks + RELEASE_THRESHOLD_MS) {
						buttons[i].buttonState = PUSHED;
					}
        			break;

        		default:
        			break; // Transitioning out of PUSHED, DOUBLE or HOLD is handled by checkButton.
       	}
	}
}



// *******************************************************
// buttons_checkButton: Function returns the new button logical state if the button
// logical state (PUSHED or RELEASED) has changed since the last call,
// otherwise returns NO_CHANGE.
buttonState_t buttons_checkButton (buttonName_t butName)
{
	// Only continue if button has changed states
	if (buttons[butName].buttonState == RELEASED ||
		buttons[butName].buttonState == WAIT1 ||
		buttons[butName].buttonState == WAIT2) return RELEASED;

	// Reset the change flag, return the button state to released
	buttonState_t currentState = buttons[butName].buttonState;
	buttons[butName].hasChanged = false;
	buttons[butName].buttonState = RELEASED;

	// Return the current state
	return currentState;
}
