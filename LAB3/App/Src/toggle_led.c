/*
 * toggle_led.c
 *
 *  Created on: Nov 16, 2026
 *      Author: HP
 */

#include "toggle_led.h"
#include "config.h"

// index = LightColor (RED, YELLOW, GREEN)
static const GpioPin road_a[3] =
{
    {LED_RED_A_GPIO_Port,    LED_RED_A_Pin},
    {LED_YELLOW_A_GPIO_Port, LED_YELLOW_A_Pin},
    {LED_GREEN_A_GPIO_Port,  LED_GREEN_A_Pin},
};

static const GpioPin road_b[3] =
{
    {LED_RED_B_GPIO_Port,    LED_RED_B_Pin},
    {LED_YELLOW_B_GPIO_Port, LED_YELLOW_B_Pin},
    {LED_GREEN_B_GPIO_Port,  LED_GREEN_B_Pin},
};

void toggle_led(LightColor color)
{
    HAL_GPIO_TogglePin(road_a[color].port, road_a[color].pin);
    HAL_GPIO_TogglePin(road_b[color].port, road_b[color].pin);
}
