/*
 * fsm_manual.c
 *
 *  Created on: Nov 3, 2026
 *      Author: HP
 */

#include "fsm_manual.h"
#include "global.h"
#include "button.h"
#include "traffic_light.h"
#include "seven_seg.h"

typedef enum
{
    MANUAL_IDLE,     // another FSM has the lights
    MANUAL_A_GREEN,  // road A green,  road B red
    MANUAL_A_YELLOW, // road A yellow, road B red
    MANUAL_B_GREEN,  // road A red,    road B green
    MANUAL_B_YELLOW  // road A red,    road B yellow
} ManualState;

static ManualState state = MANUAL_IDLE;

void fsm_manual_run(void)
{
    switch (state)
    {
    case MANUAL_IDLE:
        if (mode == MODE_MANUAL)
        {
            light_road_a = GREEN;
            light_road_b = RED;
            road_a_number = SEVEN_SEG_OFF;
            road_b_number = SEVEN_SEG_OFF;
            state = MANUAL_A_GREEN;
        }
        break;

    case MANUAL_A_GREEN:
        if (button_flag[1] == 1)
        {
            button_flag[1] = 0;
            light_road_a = YELLOW;
            state = MANUAL_A_YELLOW;
        }
        if (button_flag[0] == 1)
        {
            button_flag[0] = 0;
            mode = MODE_AUTOMATIC;
            state = MANUAL_IDLE;
        }
        break;

    case MANUAL_A_YELLOW:
        if (button_flag[1] == 1)
        {
            button_flag[1] = 0;
            light_road_a = RED;
            light_road_b = GREEN;
            state = MANUAL_B_GREEN;
        }
        if (button_flag[0] == 1)
        {
            button_flag[0] = 0;
            mode = MODE_AUTOMATIC;
            state = MANUAL_IDLE;
        }
        break;

    case MANUAL_B_GREEN:
        if (button_flag[1] == 1)
        {
            button_flag[1] = 0;
            light_road_b = YELLOW;
            state = MANUAL_B_YELLOW;
        }
        if (button_flag[0] == 1)
        {
            button_flag[0] = 0;
            mode = MODE_AUTOMATIC;
            state = MANUAL_IDLE;
        }
        break;

    case MANUAL_B_YELLOW:
        if (button_flag[1] == 1)
        {
            button_flag[1] = 0;
            light_road_a = GREEN;
            light_road_b = RED;
            state = MANUAL_A_GREEN;
        }
        if (button_flag[0] == 1)
        {
            button_flag[0] = 0;
            mode = MODE_AUTOMATIC;
            state = MANUAL_IDLE;
        }
        break;
    }
}
