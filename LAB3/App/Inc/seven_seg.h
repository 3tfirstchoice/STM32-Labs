/*
 * seven_seg.h
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 *
 *  Four 7-segment digits, scanned one by one.
 *  Road A = digits 0, 1. Road B = digits 2, 3.
 */

#ifndef INC_SEVEN_SEG_H_
#define INC_SEVEN_SEG_H_

#define SEVEN_SEG_OFF   (-1)    // number that turns a pair of digits off

// Number 0-99 (or SEVEN_SEG_OFF) shown on each road; the FSMs write them
extern volatile int road_a_number;
extern volatile int road_b_number;

// Called in the TIM2 interrupt (every 10 ms): turn on the next digit
void seven_seg_scan(void);

#endif /* INC_SEVEN_SEG_H_ */
