/*
 * software_timer.h
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */
#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include <stdint.h>


typedef enum
{
	TIMER_BLINK = 0,    // 2 Hz LED blinking
	TIMER_SEVEN_SEG,    // period of scan_seven_seg()
	TIMER_SECOND,       // 1 s count-down in mode 1
	TIMER_COUNT
} TimerId;

// Start  timer
void timer_set(TimerId id, uint32_t duration_ms);

uint8_t timer_is_expired(TimerId id);

void timer_run(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
