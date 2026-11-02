/*
 * input_processing.h
 *
 *  Created on: Nov 2, 2026
 *      Author: HP
 */

#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_

// Current mode (1 to 4), defined in input_processing.c
extern int mode;

// Call in the while (1) loop of main
void fsm_for_input_processing(void);

#endif /* INC_INPUT_PROCESSING_H_ */
