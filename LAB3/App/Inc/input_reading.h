/*
 * input_reading.h
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#define N0_OF_BUTTONS   3

// Called in the timer interrupt (every 10 ms): read and debounce the buttons
void button_reading(void);

// Return 1 while button index (0, 1, 2) is held down, otherwise 0
unsigned char is_button_pressed(unsigned char index);

// Return 1 when button index has been held down for more than 1 second
unsigned char is_button_pressed_1s(unsigned char index);

#endif /* INC_INPUT_READING_H_ */
