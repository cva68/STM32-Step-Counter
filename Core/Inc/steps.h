/*
* steps.h
*
* Stores step goal and step count, providing getter and setter functions.
*
*  Created on: May 5, 2025
*      Authors: C. Varney, A. Walker
*/

#ifndef STEPS_H
#define STEPS_H

#include <stdint.h>

// Step count getters and setters
void steps_incrementSteps(uint16_t by);
void steps_decrementSteps(uint16_t by);
uint16_t steps_getStepCount(void);
void steps_setStepCount(uint16_t steps);

// Step goal getters and setters
void steps_setStepGoal(uint16_t goal);
uint16_t steps_getStepGoal(void);
void steps_incrementStepGoal(uint16_t by);
uint16_t steps_getGoalPercentage(void);

#endif // STEPS_H
