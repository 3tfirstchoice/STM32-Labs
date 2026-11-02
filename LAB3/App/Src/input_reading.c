/*
 * input_reading.c
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#include "input_reading.h"
#include "config.h"

// button_reading() runs once per timer interrupt, so 1 second
// is (1000 / TIMER_CYCLE_MS) calls: 100 calls when the interrupt is 10 ms
#define DURATION_FOR_AUTO_INCREASING    (1000 / TIMER_CYCLE_MS)
#define BUTTON_IS_PRESSED               GPIO_PIN_RESET
#define BUTTON_IS_RELEASED              GPIO_PIN_SET

// the buffer that the final result is stored after debouncing
static GPIO_PinState buttonBuffer[N0_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
// we define two buffers for debouncing
static GPIO_PinState debounceButtonBuffer1[N0_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
static GPIO_PinState debounceButtonBuffer2[N0_OF_BUTTONS] = {BUTTON_IS_RELEASED, BUTTON_IS_RELEASED, BUTTON_IS_RELEASED};
// we define a flag for a button pressed more than 1 second
static uint8_t flagForButtonPress1s[N0_OF_BUTTONS];
// we define counter for automatically increasing the value
// after the button is pressed more than 1 second
static uint16_t counterForButtonPress1s[N0_OF_BUTTONS];

// Read the raw level of button index (0, 1, 2)
static GPIO_PinState read_button(int index)
{
    if (index == 0)
    {
        return HAL_GPIO_ReadPin(BUTTON_1_GPIO_Port, BUTTON_1_Pin);
    }
    else if (index == 1)
    {
        return HAL_GPIO_ReadPin(BUTTON_2_GPIO_Port, BUTTON_2_Pin);
    }
    else
    {
        return HAL_GPIO_ReadPin(BUTTON_3_GPIO_Port, BUTTON_3_Pin);
    }
}

void button_reading(void)
{
    for (int i = 0; i < N0_OF_BUTTONS; i++)
    {
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
        debounceButtonBuffer1[i] = read_button(i);

        // two equal readings 10 ms apart: the button is not bouncing
        if (debounceButtonBuffer1[i] == debounceButtonBuffer2[i])
        {
            buttonBuffer[i] = debounceButtonBuffer1[i];
        }

        if (buttonBuffer[i] == BUTTON_IS_PRESSED)
        {
            // if a button is pressed, we start counting
            if (counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING)
            {
                counterForButtonPress1s[i]++;
            }
            else
            {
                // the flag is turned on when 1 second has passed
                // since the button is pressed
                flagForButtonPress1s[i] = 1;
            }
        }
        else
        {
            counterForButtonPress1s[i] = 0;
            flagForButtonPress1s[i] = 0;
        }
    }
}

unsigned char is_button_pressed(unsigned char index)
{
    if (index >= N0_OF_BUTTONS) return 0;
    return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

unsigned char is_button_pressed_1s(unsigned char index)
{
    if (index >= N0_OF_BUTTONS) return 0;
    return (flagForButtonPress1s[index] == 1);
}
