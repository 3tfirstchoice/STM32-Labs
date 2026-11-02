/*
 * led.h
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#ifndef INC_LED_H_
#define INC_LED_H_

// Turn all 6 LEDs off
void turn_off_all_leds(void);

// mode 1: all off, mode 2: red, mode 3: yellow, mode 4: green
void display_mode(int mode);

// Call every 250 ms: modes 2-4 blink the LEDs of the mode color (2 Hz)
void blink_mode_leds(int mode);

#endif /* INC_LED_H_ */
