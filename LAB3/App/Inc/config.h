/*
 * config.h
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 *
 *  Pins, timing and default durations. Nothing else.
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include "main.h"

// A GPIO pin = port + pin number
typedef struct
{
    GPIO_TypeDef *port;
    uint16_t      pin;
} GpioPin;

/* ---------------------------- Pins ------------------------------- */

// Traffic light LEDs (on = GPIO_PIN_RESET)
#define LED_RED_A_GPIO_Port         GPIOA
#define LED_RED_A_Pin               GPIO_PIN_1
#define LED_YELLOW_A_GPIO_Port      GPIOA
#define LED_YELLOW_A_Pin            GPIO_PIN_2
#define LED_GREEN_A_GPIO_Port       GPIOA
#define LED_GREEN_A_Pin             GPIO_PIN_3
#define LED_RED_B_GPIO_Port         GPIOA
#define LED_RED_B_Pin               GPIO_PIN_4
#define LED_YELLOW_B_GPIO_Port      GPIOA
#define LED_YELLOW_B_Pin            GPIO_PIN_5
#define LED_GREEN_B_GPIO_Port       GPIOA
#define LED_GREEN_B_Pin             GPIO_PIN_6

// 7-segment digit enable (on = GPIO_PIN_RESET)
#define EN0_GPIO_Port               GPIOA
#define EN0_Pin                     GPIO_PIN_7
#define EN1_GPIO_Port               GPIOA
#define EN1_Pin                     GPIO_PIN_8
#define EN2_GPIO_Port               GPIOA
#define EN2_Pin                     GPIO_PIN_9
#define EN3_GPIO_Port               GPIOA
#define EN3_Pin                     GPIO_PIN_10

// 7-segment segments a-g (on = GPIO_PIN_RESET)
#define SEG_A_GPIO_Port             GPIOB
#define SEG_A_Pin                   GPIO_PIN_0
#define SEG_B_GPIO_Port             GPIOB
#define SEG_B_Pin                   GPIO_PIN_1
#define SEG_C_GPIO_Port             GPIOB
#define SEG_C_Pin                   GPIO_PIN_2
#define SEG_D_GPIO_Port             GPIOB
#define SEG_D_Pin                   GPIO_PIN_3
#define SEG_E_GPIO_Port             GPIOB
#define SEG_E_Pin                   GPIO_PIN_4
#define SEG_F_GPIO_Port             GPIOB
#define SEG_F_Pin                   GPIO_PIN_5
#define SEG_G_GPIO_Port             GPIOB
#define SEG_G_Pin                   GPIO_PIN_6

// Buttons (pressed = GPIO_PIN_RESET): 1 = mode, 2 = increase, 3 = set
#define BUTTON_1_GPIO_Port          GPIOB
#define BUTTON_1_Pin                GPIO_PIN_12
#define BUTTON_2_GPIO_Port          GPIOB
#define BUTTON_2_Pin                GPIO_PIN_13
#define BUTTON_3_GPIO_Port          GPIOB
#define BUTTON_3_Pin                GPIO_PIN_14

/* ---------------------------- Timing ----------------------------- */

#define TIMER_CYCLE_MS              10U     // TIM2 interrupt period
#define ONE_SECOND_MS               1000U   // count-down step in auto mode
#define BLINK_PERIOD_MS             250U    // LED toggle in setting modes (2 Hz)

/* ---------------------- Durations (seconds) ---------------------- */
// Rule kept by the setting modes: red = green + yellow

#define DEFAULT_RED_DURATION        5
#define DEFAULT_YELLOW_DURATION     2
#define DEFAULT_GREEN_DURATION      3
#define DURATION_MIN                1
#define DURATION_MAX                99

#endif /* INC_CONFIG_H_ */
