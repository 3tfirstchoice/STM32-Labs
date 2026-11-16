/*
 * fsm_setting.h
 *
 *  Created on: Nov 3, 2026
 *      Author: HP
 *
 *  Modes 2-4: change the red / yellow / green durations.
 */

#ifndef INC_FSM_SETTING_H_
#define INC_FSM_SETTING_H_

// Called in the main loop; leaves IDLE when mode is this FSM's
void fsm_setting_run(void);

#endif /* INC_FSM_SETTING_H_ */
