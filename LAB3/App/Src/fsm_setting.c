/*
 * fsm_setting.c
 *
 *  Created on: Nov 3, 2026
 *      Author: HP
 *
 *  road_a_number = the duration being set, road_b_number = the mode number.
 *  Button 2 increases it (1..99), button 3 saves it; after saving, the
 *  saved duration is shown (the old one if the new value was refused).
 */

#include "fsm_setting.h"
#include "global.h"
#include "config.h"
#include "button.h"
#include "software_timer.h"
#include "traffic_light.h"
#include "toggle_led.h"
#include "seven_seg.h"

typedef enum
{
    SETTING_IDLE,   // another FSM has the lights
    SETTING_RED,    // mode 2
    SETTING_YELLOW, // mode 3
    SETTING_GREEN   // mode 4
} SettingState;

static SettingState state = SETTING_IDLE;

void fsm_setting_run(void)
{
    switch (state)
    {
    case SETTING_IDLE:
        if (mode == MODE_SETTING)
        {
            light_road_a = RED;
            light_road_b = RED;
            road_a_number = red_duration;
            road_b_number = 2;
            set_timer(TIMER_SETTING_BLINK, BLINK_PERIOD_MS);
            state = SETTING_RED;
        }
        break;

    case SETTING_RED:
        if (timer_flag[TIMER_SETTING_BLINK] == 1)
        {
            set_timer(TIMER_SETTING_BLINK, BLINK_PERIOD_MS);
            toggle_led(RED);
        }
        if (button_flag[1] == 1)
        {
            button_flag[1] = 0;
            road_a_number = road_a_number % DURATION_MAX + 1;
        }
        if (button_flag[2] == 1)
        {
            button_flag[2] = 0;
            set_red_duration(road_a_number);
            road_a_number = red_duration;
        }
        if (button_flag[0] == 1)
        {
            button_flag[0] = 0;
            light_road_a = YELLOW;
            light_road_b = YELLOW;
            road_a_number = yellow_duration;
            road_b_number = 3;
            set_timer(TIMER_SETTING_BLINK, BLINK_PERIOD_MS);
            state = SETTING_YELLOW;
        }
        break;

    case SETTING_YELLOW:
        if (timer_flag[TIMER_SETTING_BLINK] == 1)
        {
            set_timer(TIMER_SETTING_BLINK, BLINK_PERIOD_MS);
            toggle_led(YELLOW);
        }
        if (button_flag[1] == 1)
        {
            button_flag[1] = 0;
            road_a_number = road_a_number % DURATION_MAX + 1;
        }
        if (button_flag[2] == 1)
        {
            button_flag[2] = 0;
            set_yellow_duration(road_a_number);
            road_a_number = yellow_duration;
        }
        if (button_flag[0] == 1)
        {
            button_flag[0] = 0;
            light_road_a = GREEN;
            light_road_b = GREEN;
            road_a_number = green_duration;
            road_b_number = 4;
            set_timer(TIMER_SETTING_BLINK, BLINK_PERIOD_MS);
            state = SETTING_GREEN;
        }
        break;

    case SETTING_GREEN:
        if (timer_flag[TIMER_SETTING_BLINK] == 1)
        {
            set_timer(TIMER_SETTING_BLINK, BLINK_PERIOD_MS);
            toggle_led(GREEN);
        }
        if (button_flag[1] == 1)
        {
            button_flag[1] = 0;
            road_a_number = road_a_number % DURATION_MAX + 1;
        }
        if (button_flag[2] == 1)
        {
            button_flag[2] = 0;
            set_green_duration(road_a_number);
            road_a_number = green_duration;
        }
        if (button_flag[0] == 1)
        {
            button_flag[0] = 0;
            mode = MODE_AUTOMATIC;
            state = SETTING_IDLE;
        }
        break;
    }
}
