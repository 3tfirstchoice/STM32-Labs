/*
 * software_timer.h
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 *
 *  One-shot software timers, ticked every TIMER_CYCLE_MS by TIM2.
 *  Each FSM owns its own timers.
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include <stdint.h>

typedef enum
{
    TIMER_AUTOMATIC_TICK = 0,   // fsm_automatic: 1 s count-down
    TIMER_SETTING_BLINK,        // fsm_setting:   250 ms LED toggle
    TIMER_COUNT
} TimerId;

// timer_flag[id] = 1 when timer id has expired
extern volatile uint8_t timer_flag[TIMER_COUNT];

// Start timer id (its flag is cleared); it expires after duration_ms
void set_timer(TimerId id, uint32_t duration_ms);

// Called in the TIM2 interrupt
void timer_run(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
