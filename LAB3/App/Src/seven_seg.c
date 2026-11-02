/*
 * seven_seg.c
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#include "seven_seg.h"
#include "config.h"

// 1 = segment on, order: a b c d e f g
int digit_table[11][7] =
{
    {1, 1, 1, 1, 1, 1, 0},   // 0
    {0, 1, 1, 0, 0, 0, 0},   // 1
    {1, 1, 0, 1, 1, 0, 1},   // 2
    {1, 1, 1, 1, 0, 0, 1},   // 3
    {0, 1, 1, 0, 0, 1, 1},   // 4
    {1, 0, 1, 1, 0, 1, 1},   // 5
    {1, 0, 1, 1, 1, 1, 1},   // 6
    {1, 1, 1, 0, 0, 0, 0},   // 7
    {1, 1, 1, 1, 1, 1, 1},   // 8
    {1, 1, 1, 1, 0, 1, 1},   // 9
    {0, 0, 0, 0, 0, 0, 0}    // BLANK
};

int led_buffer[MAX_LED] = {BLANK, BLANK, BLANK, BLANK};
int index_led = 0;

// Segment is on when its pin is GPIO_PIN_RESET
GPIO_PinState segment_level(int on)
{
    if (on == 1)
    {
        return GPIO_PIN_RESET;
    }
    return GPIO_PIN_SET;
}

void display7SEG(int num)
{
    HAL_GPIO_WritePin(SEG_A_GPIO_Port, SEG_A_Pin, segment_level(digit_table[num][0]));
    HAL_GPIO_WritePin(SEG_B_GPIO_Port, SEG_B_Pin, segment_level(digit_table[num][1]));
    HAL_GPIO_WritePin(SEG_C_GPIO_Port, SEG_C_Pin, segment_level(digit_table[num][2]));
    HAL_GPIO_WritePin(SEG_D_GPIO_Port, SEG_D_Pin, segment_level(digit_table[num][3]));
    HAL_GPIO_WritePin(SEG_E_GPIO_Port, SEG_E_Pin, segment_level(digit_table[num][4]));
    HAL_GPIO_WritePin(SEG_F_GPIO_Port, SEG_F_Pin, segment_level(digit_table[num][5]));
    HAL_GPIO_WritePin(SEG_G_GPIO_Port, SEG_G_Pin, segment_level(digit_table[num][6]));
}

// Digit is selected when its EN pin is GPIO_PIN_RESET
void update7SEG(int index)
{
    HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_SET);

    display7SEG(led_buffer[index]);

    if (index == 0)
    {
        HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, GPIO_PIN_RESET);
    }
    else if (index == 1)
    {
        HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, GPIO_PIN_RESET);
    }
    else if (index == 2)
    {
        HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, GPIO_PIN_RESET);
    }
}

void set_led_buffer(int index, int value)
{
    led_buffer[index] = value;
}

void scan_seven_seg(void)
{
    update7SEG(index_led);

    index_led++;
    if (index_led >= MAX_LED)
    {
        index_led = 0;
    }
}

void show_mode_on_seven_seg(int mode)
{
    set_led_buffer(0, BLANK);
    set_led_buffer(1, BLANK);
    set_led_buffer(2, mode / 10);
    set_led_buffer(3, mode % 10);
}

void show_value_on_seven_seg(int value)
{
    set_led_buffer(0, value / 10);
    set_led_buffer(1, value % 10);
}

void show_countdown_on_seven_seg(int ns_value, int ew_value)
{
    set_led_buffer(0, ns_value / 10);
    set_led_buffer(1, ns_value % 10);
    set_led_buffer(2, ew_value / 10);
    set_led_buffer(3, ew_value % 10);
}
