/*
 * led.c
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#include "led.h"
#include "config.h"

// LED is on when its pin is GPIO_PIN_RESET
void turn_off_all_leds(void)
{
    HAL_GPIO_WritePin(LED_RED_NS_GPIO_Port, LED_RED_NS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_NS_GPIO_Port, LED_YELLOW_NS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_NS_GPIO_Port, LED_GREEN_NS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_RED_EW_GPIO_Port, LED_RED_EW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_EW_GPIO_Port, LED_YELLOW_EW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_EW_GPIO_Port, LED_GREEN_EW_Pin, GPIO_PIN_SET);
}

// 1 = the mode LEDs are on, 0 = off (used for blinking)
int led_on = 1;

void display_mode(int mode)
{
    turn_off_all_leds();
    led_on = 1;

    if (mode == 2)
    {
        HAL_GPIO_WritePin(LED_RED_NS_GPIO_Port, LED_RED_NS_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_RED_EW_GPIO_Port, LED_RED_EW_Pin, GPIO_PIN_RESET);
    }
    else if (mode == 3)
    {
        HAL_GPIO_WritePin(LED_YELLOW_NS_GPIO_Port, LED_YELLOW_NS_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_YELLOW_EW_GPIO_Port, LED_YELLOW_EW_Pin, GPIO_PIN_RESET);
    }
    else if (mode == 4)
    {
        HAL_GPIO_WritePin(LED_GREEN_NS_GPIO_Port, LED_GREEN_NS_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_GREEN_EW_GPIO_Port, LED_GREEN_EW_Pin, GPIO_PIN_RESET);
    }
}

void blink_mode_leds(int mode)
{
    if (mode == 1)
    {
        return;
    }

    if (led_on == 1)
    {
        turn_off_all_leds();
        led_on = 0;
    }
    else
    {
        display_mode(mode);
    }
}

void set_ns_light(int color)
{
    HAL_GPIO_WritePin(LED_RED_NS_GPIO_Port, LED_RED_NS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_NS_GPIO_Port, LED_YELLOW_NS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_NS_GPIO_Port, LED_GREEN_NS_Pin, GPIO_PIN_SET);

    if (color == RED)
    {
        HAL_GPIO_WritePin(LED_RED_NS_GPIO_Port, LED_RED_NS_Pin, GPIO_PIN_RESET);
    }
    else if (color == YELLOW)
    {
        HAL_GPIO_WritePin(LED_YELLOW_NS_GPIO_Port, LED_YELLOW_NS_Pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(LED_GREEN_NS_GPIO_Port, LED_GREEN_NS_Pin, GPIO_PIN_RESET);
    }
}

void set_ew_light(int color)
{
    HAL_GPIO_WritePin(LED_RED_EW_GPIO_Port, LED_RED_EW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_EW_GPIO_Port, LED_YELLOW_EW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_EW_GPIO_Port, LED_GREEN_EW_Pin, GPIO_PIN_SET);

    if (color == RED)
    {
        HAL_GPIO_WritePin(LED_RED_EW_GPIO_Port, LED_RED_EW_Pin, GPIO_PIN_RESET);
    }
    else if (color == YELLOW)
    {
        HAL_GPIO_WritePin(LED_YELLOW_EW_GPIO_Port, LED_YELLOW_EW_Pin, GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(LED_GREEN_EW_GPIO_Port, LED_GREEN_EW_Pin, GPIO_PIN_RESET);
    }
}
