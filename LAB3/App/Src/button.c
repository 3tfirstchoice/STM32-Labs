/*
 * button.c
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#include "button.h"
#include "config.h"

#define PRESSED     GPIO_PIN_RESET
#define RELEASED    GPIO_PIN_SET

volatile uint8_t button_flag[NUMBER_OF_BUTTONS];

static const GpioPin button_pin[NUMBER_OF_BUTTONS] =
{
    {BUTTON_1_GPIO_Port, BUTTON_1_Pin},
    {BUTTON_2_GPIO_Port, BUTTON_2_Pin},
    {BUTTON_3_GPIO_Port, BUTTON_3_Pin},
};

// two raw readings 10 ms apart, and the debounced level
static GPIO_PinState reading1[NUMBER_OF_BUTTONS] = {RELEASED, RELEASED, RELEASED};
static GPIO_PinState reading2[NUMBER_OF_BUTTONS] = {RELEASED, RELEASED, RELEASED};
static GPIO_PinState stable[NUMBER_OF_BUTTONS]   = {RELEASED, RELEASED, RELEASED};

void button_scan(void)
{
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
        reading2[i] = reading1[i];
        reading1[i] = HAL_GPIO_ReadPin(button_pin[i].port, button_pin[i].pin);

        // not bouncing: two equal readings
        if (reading1[i] == reading2[i])
        {
            // released -> pressed edge
            if (stable[i] == RELEASED && reading1[i] == PRESSED)
            {
                button_flag[i] = 1;
            }
            stable[i] = reading1[i];
        }
    }
}
