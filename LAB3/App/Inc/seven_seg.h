/*
 * seven_seg.h
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#ifndef INC_SEVEN_SEG_H_
#define INC_SEVEN_SEG_H_

#define MAX_LED     4
#define BLANK       10      // value that turns a digit off

// Digit index: 0, 1 = North-South pair, 2, 3 = East-West pair
// value: 0-9, or BLANK
void set_led_buffer(int index, int value);

// Call every 10 ms: turn on the next digit (0 -> 1 -> 2 -> 3 -> 0)
void scan_seven_seg(void);

// Show the mode on the East-West pair (digits 2, 3), North-South pair off
void show_mode_on_seven_seg(int mode);

// Show a value (0-99) on the North-South pair (digits 0, 1)
void show_value_on_seven_seg(int value);

#endif /* INC_SEVEN_SEG_H_ */
