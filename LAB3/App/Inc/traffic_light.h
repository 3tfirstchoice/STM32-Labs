/*
 * traffic_light.h
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 *
 *  The 6 LEDs: road A and road B, each red / yellow / green.
 */

#ifndef INC_TRAFFIC_LIGHT_H_
#define INC_TRAFFIC_LIGHT_H_

typedef enum
{
    RED = 0,
    YELLOW,
    GREEN,
    LIGHT_OFF
} LightColor;

// Color lit on each road; the FSMs write them, traffic_light_update() shows them
extern volatile LightColor light_road_a;
extern volatile LightColor light_road_b;

// Called in the TIM2 interrupt (every 10 ms)
void traffic_light_update(void);

#endif /* INC_TRAFFIC_LIGHT_H_ */
