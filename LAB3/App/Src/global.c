/*
 * global.c
 *
 *  Created on: Nov 16, 2026
 *      Author: HP
 */

#include "global.h"
#include "config.h"

Mode mode = MODE_AUTOMATIC;

int red_duration = DEFAULT_RED_DURATION;
int yellow_duration = DEFAULT_YELLOW_DURATION;
int green_duration = DEFAULT_GREEN_DURATION;

// Each one keeps red = green + yellow; a value that breaks it is refused
void set_red_duration(int duration)
{
    if (duration - yellow_duration >= DURATION_MIN)
    {
        red_duration = duration;
        green_duration = duration - yellow_duration;
    }
}

void set_yellow_duration(int duration)
{
    if (green_duration + duration <= DURATION_MAX)
    {
        yellow_duration = duration;
        red_duration = green_duration + duration;
    }
}

void set_green_duration(int duration)
{
    if (duration + yellow_duration <= DURATION_MAX)
    {
        green_duration = duration;
        red_duration = duration + yellow_duration;
    }
}
