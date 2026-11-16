/*
 * button.h
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 *
 *  Debounced buttons.
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <stdint.h>

#define NUMBER_OF_BUTTONS   3

// button_flag[i] = 1 when button i+1 was pressed; the FSM that uses it clears it
extern volatile uint8_t button_flag[NUMBER_OF_BUTTONS];

// Called in the TIM2 interrupt (every 10 ms): read and debounce the buttons
void button_scan(void);

#endif /* INC_BUTTON_H_ */
