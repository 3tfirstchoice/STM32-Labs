/*
 * button.c
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#include "button.h"
#include "config.h"

// key_reg0, key_reg1: the last two readings
// key_reg2: the state accepted after debouncing
int key_reg0[NO_OF_BUTTONS] = {GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET};
int key_reg1[NO_OF_BUTTONS] = {GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET};
int key_reg2[NO_OF_BUTTONS] = {GPIO_PIN_SET, GPIO_PIN_SET, GPIO_PIN_SET};

int button_flag[NO_OF_BUTTONS] = {0, 0, 0};

// Read the raw level of button index
int read_button(int index)
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
    for (int i = 0; i < NO_OF_BUTTONS; i++)
    {
        key_reg0[i] = key_reg1[i];
        key_reg1[i] = read_button(i);

        // Two equal readings 10 ms apart: the button is not bouncing
        if (key_reg0[i] == key_reg1[i])
        {
            if (key_reg2[i] != key_reg1[i])
            {
                key_reg2[i] = key_reg1[i];

                if (key_reg2[i] == GPIO_PIN_RESET)
                {
                    button_flag[i] = 1;
                }
            }
        }
    }
}

int is_button_pressed(int index)
{
    if (button_flag[index] == 1)
    {
        button_flag[index] = 0;
        return 1;
    }
    return 0;
}
