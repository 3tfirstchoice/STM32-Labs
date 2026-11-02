/*
 * config.h
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#ifndef INC_CONFIG_H_
#define INC_CONFIG_H_

#include "main.h"

// Traffic light LEDs
#define LED_RED_NS_GPIO_Port        GPIOA
#define LED_RED_NS_Pin              GPIO_PIN_1
#define LED_YELLOW_NS_GPIO_Port     GPIOA
#define LED_YELLOW_NS_Pin           GPIO_PIN_2
#define LED_GREEN_NS_GPIO_Port      GPIOA
#define LED_GREEN_NS_Pin            GPIO_PIN_3
#define LED_RED_EW_GPIO_Port        GPIOA
#define LED_RED_EW_Pin              GPIO_PIN_4
#define LED_YELLOW_EW_GPIO_Port     GPIOA
#define LED_YELLOW_EW_Pin           GPIO_PIN_5
#define LED_GREEN_EW_GPIO_Port      GPIOA
#define LED_GREEN_EW_Pin            GPIO_PIN_6

// 7-segment digit
#define EN0_GPIO_Port               GPIOA
#define EN0_Pin                     GPIO_PIN_7
#define EN1_GPIO_Port               GPIOA
#define EN1_Pin                     GPIO_PIN_8
#define EN2_GPIO_Port               GPIOA
#define EN2_Pin                     GPIO_PIN_9
#define EN3_GPIO_Port               GPIOA
#define EN3_Pin                     GPIO_PIN_10

// 7-segment segment lines a-g
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

/* Buttons 1 = select mode 2 = increase 3 = set */
#define BUTTON_1_GPIO_Port          GPIOB
#define BUTTON_1_Pin                GPIO_PIN_12
#define BUTTON_2_GPIO_Port          GPIOB
#define BUTTON_2_Pin                GPIO_PIN_13
#define BUTTON_3_GPIO_Port          GPIOB
#define BUTTON_3_Pin                GPIO_PIN_14

/* ------------------------------------------------------------------ */
/* Timer                                                               */
/* ------------------------------------------------------------------ */

#define TIMER_CYCLE_MS              10U
#define BLINK_TOGGLE_PERIOD_MS      250U
#define BUTTON_READ_PERIOD_MS       10U
#define SEVEN_SEG_SCAN_PERIOD_MS    10U
#define ONE_SECOND_MS               1000U

/* ------------------------------------------------------------------ */
/* Traffic light durations (seconds)                                   */
/* ------------------------------------------------------------------ */

#define DEFAULT_RED_DURATION        5
#define DEFAULT_YELLOW_DURATION     2
#define DEFAULT_GREEN_DURATION      3
#define DURATION_MAX                99
#define DURATION_MIN                1

#endif /* INC_CONFIG_H_ */
