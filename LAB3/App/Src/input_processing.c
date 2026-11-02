/*
 * input_processing.c
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#include "input_processing.h"
#include "input_reading.h"
#include "config.h"
#include "led.h"
#include "seven_seg.h"

enum ButtonState { BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND };
// one FSM state for each button
enum ButtonState buttonState[N0_OF_BUTTONS] = {BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED};

int mode = 1;

int red_duration = DEFAULT_RED_DURATION;         // values in use
int yellow_duration = DEFAULT_YELLOW_DURATION;
int temp_value = 0;                              // value being changed in modes 2-4

// Run the FSM of button index (section 4.4).
// Return 1 once when the button goes from released to pressed, otherwise 0.
int fsm_for_button(int index)
{
    int just_pressed = 0;

    switch (buttonState[index])
    {
    case BUTTON_RELEASED:
        if (is_button_pressed(index))
        {
            buttonState[index] = BUTTON_PRESSED;
            just_pressed = 1;
        }
        break;
    case BUTTON_PRESSED:
        if (!is_button_pressed(index))
        {
            buttonState[index] = BUTTON_RELEASED;
        }
        else
        {
            if (is_button_pressed_1s(index))
            {
                buttonState[index] = BUTTON_PRESSED_MORE_THAN_1_SECOND;
            }
        }
        break;
    case BUTTON_PRESSED_MORE_THAN_1_SECOND:
        if (!is_button_pressed(index))
        {
            buttonState[index] = BUTTON_RELEASED;
        }
        break;
    }

    return just_pressed;
}

void fsm_for_input_processing(void)
{
    int button1 = fsm_for_button(0);
    int button2 = fsm_for_button(1);
    int button3 = fsm_for_button(2);

    // Button 1: go to the next mode (4 -> 1)
    if (button1 == 1)
    {
        mode++;
        if (mode > 4)
        {
            mode = 1;
        }
        display_mode(mode);
        show_mode_on_seven_seg(mode);

        // start from the duration in use of the mode color
        if (mode == 2)
        {
            temp_value = red_duration;
            show_value_on_seven_seg(temp_value);
        }
        else if (mode == 3)
        {
            temp_value = yellow_duration;
            show_value_on_seven_seg(temp_value);
        }
    }

    // Mode 2: change the red duration, mode 3: change the yellow duration
    if (mode == 2 || mode == 3)
    {
        // Button 2: increase the value (99 -> 1)
        if (button2 == 1)
        {
            temp_value++;
            if (temp_value > DURATION_MAX)
            {
                temp_value = DURATION_MIN;
            }
            show_value_on_seven_seg(temp_value);
        }

        // Button 3: set the value
        if (button3 == 1)
        {
            if (mode == 2)
            {
                red_duration = temp_value;
            }
            else
            {
                yellow_duration = temp_value;
            }
        }
    }
}
