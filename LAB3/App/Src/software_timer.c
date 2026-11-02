/*
 * software_timer.c
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#include "software_timer.h"
#include "config.h"


static volatile uint32_t timer_counter[TIMER_COUNT];
static volatile uint8_t  timer_flag[TIMER_COUNT];

void timer_set(TimerId id, uint32_t duration_ms)
{
    uint32_t ticks = duration_ms / TIMER_CYCLE_MS;

    if (ticks == 0)
    {
        ticks = 1;
    }

    timer_flag[id] = 0;
    timer_counter[id] = ticks;
}

uint8_t timer_is_expired(TimerId id)
{
    return timer_flag[id];
}

void timer_run(void)
{
    for (uint8_t i = 0; i < TIMER_COUNT; i++)
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

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
        timer_run();
}
