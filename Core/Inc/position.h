/*
 * position.h
 *
 *  Created on: May 12, 2025
 *      Author: awa158
 */

#ifndef POSITION_H_
#define POSITION_H_

void position_init(void);
int16_t get_filtered_x(void);
int16_t get_filtered_y(void);
int16_t get_filtered_z(void);
uint32_t get_mag(void);

#endif /* INC_POSITION_H_ */
