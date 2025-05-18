/*
 * pot.c
 *
 * Potentiometer abstraction, handles scaling from raw values to reasonable
 * step goal values (between 500 and 15000)
 *
 *  Created on: Apr 14, 2025
 *      Authors: C. Varney, A. Walker
 */

#ifndef POT_H
#define POT_H

#include <stdint.h>
#include "adc_controller.h"

uint16_t pot_getRawValue(void);
uint16_t pot_getScaledValue(void);

#endif // POT_H
