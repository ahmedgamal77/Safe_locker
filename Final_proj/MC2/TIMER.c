/*
 * TIMER.c
 *
 *  Created on: Oct 3, 2020
 *      Author: ahmed
 */

#include "TIMER.h"


static volatile void(*timer1)(void)= NULL;


void TIMER_Init(struct TIMER_init *i){

		SREG |= (1 << 7);
		SET_BIT(TCCR1A,FOC1A);
		OCR1A= i->comp_value;
		//timer mode
		if(i->mode==0){
			CLEAR_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
			SET_BIT(TIMSK,TOIE1);

		}
		else if(i->mode==1){
			CLEAR_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
			SET_BIT(TIMSK,OCIE1A);
		}

		// clock select
		if(i->prescaler==1){
			CLEAR_BIT(TCCR1B,CS12);
			CLEAR_BIT(TCCR1B,CS11);
			SET_BIT(TCCR1B,CS10);
		}
		else if(i->prescaler==8){
			CLEAR_BIT(TCCR1B,CS12);
			SET_BIT(TCCR1B,CS11);
			CLEAR_BIT(TCCR1B,CS10);
		}
		else if(i->prescaler==64){
			CLEAR_BIT(TCCR1B,CS12);
			SET_BIT(TCCR1B,CS11);
			SET_BIT(TCCR1B,CS10);
		}
		else if(i->prescaler==256){
			SET_BIT(TCCR1B,CS12);
			CLEAR_BIT(TCCR1B,CS11);
			CLEAR_BIT(TCCR1B,CS10);
		}
		else if(i->prescaler==1024){
			SET_BIT(TCCR1B,CS12);
			CLEAR_BIT(TCCR1B,CS11);
			SET_BIT(TCCR1B,CS10);
		}

		// compare match output mode
		if(i->comp_match_mode==0){
			CLEAR_BIT(TCCR1A,COM1A1);
			CLEAR_BIT(TCCR1A,COM1A0);
		}
		else if(i->comp_match_mode==1){
			SET_BIT(DDRD,PD5);
			CLEAR_BIT(TCCR1A,COM1A1);
			SET_BIT(TCCR1A,COM1A0);
		}
		else if(i->comp_match_mode==2){
			SET_BIT(DDRD,PD5);
			SET_BIT(TCCR1A,COM1A1);
			CLEAR_BIT(TCCR1A,COM1A0);
		}
		else if(i->comp_match_mode==3){
			SET_BIT(DDRD,PD5);
			SET_BIT(TCCR1A,COM1A1);
			SET_BIT(TCCR1A,COM1A0);
		}






}





void TIMER_Start(uint16 clk,uint16 comp_value){



			OCR1A= comp_value;



			// clock select
			if(clk==1){
				CLEAR_BIT(TCCR1B,CS12);
				CLEAR_BIT(TCCR1B,CS11);
				SET_BIT(TCCR1B,CS10);
			}
			else if(clk==8){
				CLEAR_BIT(TCCR1B,CS12);
				SET_BIT(TCCR1B,CS11);
				CLEAR_BIT(TCCR1B,CS10);
			}
			else if(clk==64){
				CLEAR_BIT(TCCR1B,CS12);
				SET_BIT(TCCR1B,CS11);
				SET_BIT(TCCR1B,CS10);
			}
			else if(clk==256){
				SET_BIT(TCCR1B,CS12);
				CLEAR_BIT(TCCR1B,CS11);
				CLEAR_BIT(TCCR1B,CS10);
			}
			else if(clk==1024){
				SET_BIT(TCCR1B,CS12);
				CLEAR_BIT(TCCR1B,CS11);
				SET_BIT(TCCR1B,CS10);
			}







}
void TIMER_Stop(void){


	// clock select
		CLEAR_BIT(TCCR1B,CS12);
		CLEAR_BIT(TCCR1B,CS11);
		CLEAR_BIT(TCCR1B,CS10);



}


void TIMER_Timer1SetCallBack(void(*ptr)(void)){
	timer1=ptr;
}


ISR(TIMER1_COMPA_vect){
	if(timer1!= NULL){
		(*timer1)();
	}
}


ISR(TIMER1_OVF_vect){
	if(timer1!= NULL){
		(*timer1)();
	}
}

