/*
 * traffic_light.h
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

// Mode 1: start again from "NS green, EW red" with the durations in use
void traffic_reset(void);

// Mode 1: call every 1 second to count down and change the lights
void traffic_run(void);

#endif /* INC_TRAFFIC_LIGHT_H_ */
