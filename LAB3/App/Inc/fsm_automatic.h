/*
 * fsm_automatic.h
 *
 *  Created on: Nov 3, 2026
 *      Author: HP
 *
 *  Mode 1: the lights run by themselves.
 */

#ifndef INC_FSM_AUTOMATIC_H_
#define INC_FSM_AUTOMATIC_H_

// Called in the main loop; leaves IDLE when mode is this FSM's
void fsm_automatic_run(void);

#endif /* INC_FSM_AUTOMATIC_H_ */
