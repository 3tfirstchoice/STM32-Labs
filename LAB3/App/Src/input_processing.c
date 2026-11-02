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
#include "traffic_light.h"

enum ButtonState { BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND };
// one FSM state for each button
enum ButtonState buttonState[N0_OF_BUTTONS] = {BUTTON_RELEASED, BUTTON_RELEASED, BUTTON_RELEASED};

int mode = 1;

int red_duration = DEFAULT_RED_DURATION;         // values in use
int yellow_duration = DEFAULT_YELLOW_DURATION;
int green_duration = DEFAULT_GREEN_DURATION;
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

// Button 3: save temp_value to the mode color and keep red = green + yellow.
//   mode 2 (red):    green = red - yellow
//   mode 3 (yellow): red = green + yellow
//   mode 4 (green):  red = green + yellow
void set_duration(void)
{
    if (mode == 2)
    {
        int new_green = temp_value - yellow_duration;
        if (new_green >= DURATION_MIN)
        {
            red_duration = temp_value;
            green_duration = new_green;
        }
        else
        {
            temp_value = red_duration;
        }
    }
    else if (mode == 3)
    {
        int new_red = green_duration + temp_value;
        if (new_red <= DURATION_MAX)
        {
            yellow_duration = temp_value;
            red_duration = new_red;
        }
        else
        {
            temp_value = yellow_duration;
        }
    }
    else if (mode == 4)
    {
        int new_red = temp_value + yellow_duration;
        if (new_red <= DURATION_MAX)
        {
            green_duration = temp_value;
            red_duration = new_red;
        }
        else
        {
            temp_value = green_duration;
        }
    }

    show_value_on_seven_seg(temp_value);
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
        if (mode == 1)
        {
            // back to the normal mode: run the traffic light again
            traffic_reset();
        }
        else
        {
            display_mode(mode);
            show_mode_on_seven_seg(mode);
        }

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
        else if (mode == 4)
        {
            temp_value = green_duration;
            show_value_on_seven_seg(temp_value);
        }
    }

    // Modes 2, 3, 4: change the red, yellow, green duration
    if (mode == 2 || mode == 3 || mode == 4)
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

        // Button 3: set the value and keep red = green + yellow
        if (button3 == 1)
        {
            set_duration();
        }
    }
}
