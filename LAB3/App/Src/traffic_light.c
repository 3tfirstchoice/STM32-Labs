/*
 * traffic_light.c
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#include "traffic_light.h"
#include "input_processing.h"
#include "led.h"
#include "seven_seg.h"
#include "software_timer.h"
#include "config.h"

//   State       North-South   East-West
//   NS_GREEN    green         red
//   NS_YELLOW   yellow        red
//   EW_GREEN    red           green
//   EW_YELLOW   red           yellow
enum TrafficState { NS_GREEN, NS_YELLOW, EW_GREEN, EW_YELLOW };
enum TrafficState trafficState = NS_GREEN;

// seconds left of the color shown on each road
int ns_counter = 0;
int ew_counter = 0;

// Light the LEDs of the current state and show both counters
void show_traffic(void)
{
    if (trafficState == NS_GREEN)
    {
        set_ns_light(GREEN);
        set_ew_light(RED);
    }
    else if (trafficState == NS_YELLOW)
    {
        set_ns_light(YELLOW);
        set_ew_light(RED);
    }
    else if (trafficState == EW_GREEN)
    {
        set_ns_light(RED);
        set_ew_light(GREEN);
    }
    else
    {
        set_ns_light(RED);
        set_ew_light(YELLOW);
    }

    show_countdown_on_seven_seg(ns_counter, ew_counter);
}

void traffic_reset(void)
{
    trafficState = NS_GREEN;
    ns_counter = green_duration;
    ew_counter = red_duration;
    show_traffic();

    // count a full second before the first step
    timer_set(TIMER_SECOND, ONE_SECOND_MS);
}

void traffic_run(void)
{
    ns_counter--;
    ew_counter--;

    // red = green + yellow
    switch (trafficState)
    {
    case NS_GREEN:
        if (ns_counter <= 0)
        {
            trafficState = NS_YELLOW;
            ns_counter = yellow_duration;
        }
        break;
    case NS_YELLOW:
        if (ns_counter <= 0)
        {
            trafficState = EW_GREEN;
            ns_counter = red_duration;
            ew_counter = green_duration;
        }
        break;
    case EW_GREEN:
        if (ew_counter <= 0)
        {
            trafficState = EW_YELLOW;
            ew_counter = yellow_duration;
        }
        break;
    case EW_YELLOW:
        if (ew_counter <= 0)
        {
            trafficState = NS_GREEN;
            ns_counter = green_duration;
            ew_counter = red_duration;
        }
        break;
    }

    show_traffic();
}
