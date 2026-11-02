/*
 * button.h
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#define NO_OF_BUTTONS   3

// Call every 10 ms
void button_reading(void);

// Return 1 once for each press of button index
int is_button_pressed(int index);

#endif /* INC_BUTTON_H_ */
