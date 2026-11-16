/*
 * fsm_manual.h
 *
 *  Created on: Nov 3, 2026
 *      Author: HP
 *
 *  Manual mode: button 2 moves the lights to the next phase, no time shown.
 */

#ifndef INC_FSM_MANUAL_H_
#define INC_FSM_MANUAL_H_

// Called in the main loop; leaves IDLE when mode is this FSM's
void fsm_manual_run(void);

#endif /* INC_FSM_MANUAL_H_ */
