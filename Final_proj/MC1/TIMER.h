/*
 * TIMER.h
 *
 *  Created on: Sep 30, 2020
 *      Author: ahmed
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

struct TIMER_init{
	uint8 mode; /*  0 : overflow mode
					1: compare mode */
	uint16 prescaler; /* 1 : no prescaling , values (8,64,,256,1024) */
	uint16 comp_value;
	uint8 comp_match_mode; /* 0 : OC0 disconnected
							  1 : OC0 toggle on compare match
							  2 : OC0 clear on compare match
							  3 : OC0 Set on compare match */



};
void TIMER_Init(struct TIMER_init *i);
void TIMER_Start(uint16 clk,uint16 comp_value);
void TIMER_Stop(void);


void TIMER_Timer1SetCallBack(void(*ptr)(void));



#endif /* TIMER_H_ */
