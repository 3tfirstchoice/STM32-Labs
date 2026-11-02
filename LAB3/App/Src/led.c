/*
 * led.c
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#include "led.h"
#include "config.h"

// LED is on when its pin is GPIO_PIN_RESET
void display_mode(int mode)
{
    HAL_GPIO_WritePin(LED_RED_NS_GPIO_Port, LED_RED_NS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_NS_GPIO_Port, LED_YELLOW_NS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_NS_GPIO_Port, LED_GREEN_NS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_RED_EW_GPIO_Port, LED_RED_EW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_YELLOW_EW_GPIO_Port, LED_YELLOW_EW_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LED_GREEN_EW_GPIO_Port, LED_GREEN_EW_Pin, GPIO_PIN_SET);

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
