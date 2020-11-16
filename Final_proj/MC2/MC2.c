/*
 * MC2.c
 *
 *  Created on: Oct 15, 2020
 *      Author: ahmed
 */


#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"
#include "uart.h"
#include "EEPROM.h"
#include "motor.h"
#include "TIMER.h"

uint8 FLAG=0;
void DI(void){
	FLAG=1;
	TIMER_Stop();
}

uint8 compareArray(uint8 a[],uint8 b[]);
int main(void){
	struct TIMER_init ti;
		ti.comp_match_mode = 0 ;
		ti.comp_value = 0 ;
		ti.mode = 1 ;
		ti.prescaler = 0;
		TIMER_Init(&ti);
		TIMER_Timer1SetCallBack(DI);


	uint8 p1[4],p2[4],i;
	struct UART_init ur;
	ur.baud_rate = 9600;
	ur.char_size = 8 ;
	ur.parity_mode = 0 ;
	ur.stop_bit = 0;
	EEPROM_init();

	UART_Init(&ur);
	while(UART_RecieveByte() != 'r'){}
	UART_SendByte('r');

	while(1){
		uint8 op = UART_RecieveByte();
		switch(op){
		case'*':

			UART_SendByte('*');
			for(i=0;i<4;i++){
				p1[i]=UART_RecieveByte();
				UART_SendByte('*');

			}
			while(UART_RecieveByte() != '*'){}
			for(i=0;i<4;i++){
				p2[i]=UART_RecieveByte();
				UART_SendByte('*');

			}
			if(compareArray(p1,p2)==1){
				UART_SendByte(1);
				for(i=0;i<4;i++){
					EEPROM_writeByte((0x000 | i),p1[i]);

					}

			}
			else{UART_SendByte(0);}


			break;
		case'#':
			UART_SendByte('#');
			for(i=0;i<4;i++){
				p1[i]=UART_RecieveByte();

				UART_SendByte('#');

				}
			for(i=0;i<4;i++){
				EEPROM_readByte((0x000 | i),&p2[i]);


					}
			if(compareArray(p1,p2)==1){
				UART_SendByte(1);

				if(UART_RecieveByte()=='#')
				{
					motor_on_clk_wise();
					TIMER_Start(1024,31248);
								while(FLAG==0){};
								FLAG=0;
					motor_off();
					TIMER_Start(1024,15624);
								while(FLAG==0){};
								FLAG=0;
					motor_on_anti_clk_wise();
					TIMER_Start(1024,31248);
								while(FLAG==0){};
								FLAG=0;
					motor_off();
				}

			}
			else{
				UART_SendByte(0);
				if(UART_RecieveByte()=='#')
				{
				DDRC |= (1 << 7);
				PORTC |= (1 << 7);
				TIMER_Start(1024,15624);
							while(FLAG==0){};
							FLAG=0;
				PORTC &= ~(1 << 7);
				}
			}
			break;
		}



	}




}
uint8 compareArray(uint8 a[],uint8 b[])	{
	int i;
	for(i=0;i<4;i++){
		if(a[i]!=b[i])
			return 0;
	}
	return 1;
}

