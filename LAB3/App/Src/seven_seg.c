/*
 * seven_seg.c
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#include "seven_seg.h"
#include "config.h"

#define NUMBER_OF_DIGITS    4

volatile int road_a_number = SEVEN_SEG_OFF;
volatile int road_b_number = SEVEN_SEG_OFF;

static const GpioPin enable_pin[NUMBER_OF_DIGITS] =
{
    {EN0_GPIO_Port, EN0_Pin},
    {EN1_GPIO_Port, EN1_Pin},
    {EN2_GPIO_Port, EN2_Pin},
    {EN3_GPIO_Port, EN3_Pin},
};

static const GpioPin segment_pin[7] =
{
    {SEG_A_GPIO_Port, SEG_A_Pin},
    {SEG_B_GPIO_Port, SEG_B_Pin},
    {SEG_C_GPIO_Port, SEG_C_Pin},
    {SEG_D_GPIO_Port, SEG_D_Pin},
    {SEG_E_GPIO_Port, SEG_E_Pin},
    {SEG_F_GPIO_Port, SEG_F_Pin},
    {SEG_G_GPIO_Port, SEG_G_Pin},
};

// bit 0 = segment a ... bit 6 = segment g, 1 = segment on
static const uint8_t digit_pattern[10] =
{
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F
};

static int current_digit = 0;

void seven_seg_scan(void)
{
    // digits 0, 1 show road A, digits 2, 3 show road B (tens, then units)
    int number = (current_digit < 2) ? road_a_number : road_b_number;
    int digit_value = (current_digit % 2 == 0) ? number / 10 : number % 10;
    uint8_t pattern = (number < 0) ? 0 : digit_pattern[digit_value];

    // all digits off while the segments change
    for (int digit = 0; digit < NUMBER_OF_DIGITS; digit++)
    {
        HAL_GPIO_WritePin(enable_pin[digit].port, enable_pin[digit].pin, GPIO_PIN_SET);
    }

    for (int segment = 0; segment < 7; segment++)
    {
        HAL_GPIO_WritePin(segment_pin[segment].port, segment_pin[segment].pin,
                          ((pattern >> segment) & 1) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    }

    HAL_GPIO_WritePin(enable_pin[current_digit].port, enable_pin[current_digit].pin, GPIO_PIN_RESET);

    current_digit = (current_digit + 1) % NUMBER_OF_DIGITS;
}
