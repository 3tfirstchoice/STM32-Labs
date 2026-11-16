/*
 * global.h
 *
 *  Created on: Nov 16, 2026
 *      Author: HP
 *
 *  Data shared by the three FSMs. An FSM never calls another FSM: it only
 *  writes mode, and each FSM leaves IDLE when mode is its own.
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

typedef enum
{
    MODE_AUTOMATIC,     // fsm_automatic has the lights (mode 1)
    MODE_MANUAL,        // fsm_manual has the lights
    MODE_SETTING        // fsm_setting has the lights (modes 2-4)
} Mode;

extern Mode mode;

// Durations in use (seconds), changed by fsm_setting, always red = green + yellow
extern int red_duration;
extern int yellow_duration;
extern int green_duration;

// Save a new duration and update red / green so red = green + yellow stays
// true; a value that would break the rule (or leave 1..99) is refused
void set_red_duration(int duration);
void set_yellow_duration(int duration);
void set_green_duration(int duration);

#endif /* INC_GLOBAL_H_ */
