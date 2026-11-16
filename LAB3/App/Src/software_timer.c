/*
 * software_timer.c
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#include "software_timer.h"
#include "config.h"

volatile uint8_t timer_flag[TIMER_COUNT];
static volatile uint32_t timer_counter[TIMER_COUNT];

void set_timer(TimerId id, uint32_t duration_ms)
{
    // counter first, then flag: an interrupt in between cannot leave
    // an old expiry flag behind
    timer_counter[id] = duration_ms / TIMER_CYCLE_MS;
    timer_flag[id] = 0;
}

void timer_run(void)
{
    for (int i = 0; i < TIMER_COUNT; i++)
    {
        if (timer_counter[i] > 0)
        {
            timer_counter[i]--;
            if (timer_counter[i] == 0)
            {
                timer_flag[i] = 1;
            }
        }
    }
}
