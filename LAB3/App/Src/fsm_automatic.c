/*
 * fsm_automatic.c
 *
 *  Created on: Nov 3, 2026
 *      Author: HP
 *
 *  road_a_number / road_b_number are the seconds left on each road.
 */

#include "fsm_automatic.h"
#include "global.h"
#include "config.h"
#include "button.h"
#include "software_timer.h"
#include "traffic_light.h"
#include "seven_seg.h"

typedef enum
{
    AUTOMATIC_IDLE,     // another FSM has the lights
    AUTOMATIC_A_GREEN,  // road A green,  road B red
    AUTOMATIC_A_YELLOW, // road A yellow, road B red
    AUTOMATIC_B_GREEN,  // road A red,    road B green
    AUTOMATIC_B_YELLOW  // road A red,    road B yellow
} AutomaticState;

static AutomaticState state = AUTOMATIC_IDLE;

void fsm_automatic_run(void)
{
    switch (state)
    {
    case AUTOMATIC_IDLE:
        if (mode == MODE_AUTOMATIC)
        {
            light_road_a = GREEN;
            light_road_b = RED;
            road_a_number = green_duration;
            road_b_number = red_duration;
            set_timer(TIMER_AUTOMATIC_TICK, ONE_SECOND_MS);
            state = AUTOMATIC_A_GREEN;
        }
        break;

    case AUTOMATIC_A_GREEN:
        if (timer_flag[TIMER_AUTOMATIC_TICK] == 1)
        {
            set_timer(TIMER_AUTOMATIC_TICK, ONE_SECOND_MS);
            road_a_number--;
            road_b_number--;
        }
        if (road_a_number == 0)
        {
            light_road_a = YELLOW;
            road_a_number = yellow_duration;
            road_b_number = yellow_duration;    // road B red left = yellow
            state = AUTOMATIC_A_YELLOW;
        }
        if (button_flag[0] == 1)
        {
            button_flag[0] = 0;
            mode = MODE_SETTING;
            state = AUTOMATIC_IDLE;
        }
        if (button_flag[1] == 1)
        {
            button_flag[1] = 0;
            mode = MODE_MANUAL;
            state = AUTOMATIC_IDLE;
        }
        break;

    case AUTOMATIC_A_YELLOW:
        if (timer_flag[TIMER_AUTOMATIC_TICK] == 1)
        {
            set_timer(TIMER_AUTOMATIC_TICK, ONE_SECOND_MS);
            road_a_number--;
            road_b_number--;
        }
        if (road_a_number == 0)
        {
            light_road_a = RED;
            light_road_b = GREEN;
            road_a_number = red_duration;
            road_b_number = green_duration;
            state = AUTOMATIC_B_GREEN;
        }
        if (button_flag[0] == 1)
        {
            button_flag[0] = 0;
            mode = MODE_SETTING;
            state = AUTOMATIC_IDLE;
        }
        if (button_flag[1] == 1)
        {
            button_flag[1] = 0;
            mode = MODE_MANUAL;
            state = AUTOMATIC_IDLE;
        }
        break;

    case AUTOMATIC_B_GREEN:
        if (timer_flag[TIMER_AUTOMATIC_TICK] == 1)
        {
            set_timer(TIMER_AUTOMATIC_TICK, ONE_SECOND_MS);
            road_a_number--;
            road_b_number--;
        }
        if (road_b_number == 0)
        {
            light_road_b = YELLOW;
            road_a_number = yellow_duration;    // road A red left = yellow
            road_b_number = yellow_duration;
            state = AUTOMATIC_B_YELLOW;
        }
        if (button_flag[0] == 1)
        {
            button_flag[0] = 0;
            mode = MODE_SETTING;
            state = AUTOMATIC_IDLE;
        }
        if (button_flag[1] == 1)
        {
            button_flag[1] = 0;
            mode = MODE_MANUAL;
            state = AUTOMATIC_IDLE;
        }
        break;

    case AUTOMATIC_B_YELLOW:
        if (timer_flag[TIMER_AUTOMATIC_TICK] == 1)
        {
            set_timer(TIMER_AUTOMATIC_TICK, ONE_SECOND_MS);
            road_a_number--;
            road_b_number--;
        }
        if (road_b_number == 0)
        {
            light_road_a = GREEN;
            light_road_b = RED;
            road_a_number = green_duration;
            road_b_number = red_duration;
            state = AUTOMATIC_A_GREEN;
        }
        if (button_flag[0] == 1)
        {
            button_flag[0] = 0;
            mode = MODE_SETTING;
            state = AUTOMATIC_IDLE;
        }
        if (button_flag[1] == 1)
        {
            button_flag[1] = 0;
            mode = MODE_MANUAL;
            state = AUTOMATIC_IDLE;
        }
        break;
    }
}
