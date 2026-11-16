/*
 * traffic_light.c
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#include "traffic_light.h"
#include "config.h"

volatile LightColor light_road_a = LIGHT_OFF;
volatile LightColor light_road_b = LIGHT_OFF;

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

// LED on = GPIO_PIN_RESET: only the LED of the chosen color is on.
// Pins are written only when a color changes, so the toggle_led()
// blinking done by fsm_setting is not overwritten.
void traffic_light_update(void)
{
    static LightColor shown_road_a = LIGHT_OFF;
    static LightColor shown_road_b = LIGHT_OFF;

    if (light_road_a == shown_road_a && light_road_b == shown_road_b)
    {
        return;
    }
    shown_road_a = light_road_a;
    shown_road_b = light_road_b;

    for (int color = RED; color <= GREEN; color++)
    {
        HAL_GPIO_WritePin(road_a[color].port, road_a[color].pin,
                          (color == light_road_a) ? GPIO_PIN_RESET : GPIO_PIN_SET);
        HAL_GPIO_WritePin(road_b[color].port, road_b[color].pin,
                          (color == light_road_b) ? GPIO_PIN_RESET : GPIO_PIN_SET);
    }
}
