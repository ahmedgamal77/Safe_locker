/*
 * MC1.c
 *
 *  Created on: Oct 15, 2020
 *      Author: ahmed
 */

#include "common_macros.h"
#include "LCD_Driver.h"
#include "keypad.h"
#include "micro_config.h"
#include "std_types.h"
#include "uart.h"
#include "TIMER.h"


uint8 SetNewPassWord(void);
uint8 CheckPassWord(void);
void Takeoption(uint8 op);
uint8 FLAG=0;
void DI(void){
	FLAG=1;
	TIMER_Stop();
}
int main(void){
	struct TIMER_init ti;
	ti.comp_match_mode = 0 ;
	ti.comp_value = 0 ;
	ti.mode = 1 ;
	ti.prescaler = 0;
	TIMER_Init(&ti);
	TIMER_Timer1SetCallBack(DI);




	struct UART_init ur;
	ur.baud_rate = 9600;
	ur.char_size = 8 ;
	ur.parity_mode = 0 ;
	ur.stop_bit = 0;
	UART_Init(&ur);

	SREG |= (1 << 7);
	LCD_Init();


	LCD_DisplayStr("Welcome");
	UART_SendByte('r');
	while(UART_RecieveByte() != 'r'){}

	_delay_ms(500);
	LCD_ClearScreen();

	while(SetNewPassWord() == 0){};
	LCD_ClearScreen();
	LCD_DisplayStr("Done");
	_delay_ms(1000);







	while(1){


	uint8 op;
	LCD_ClearScreen();
	LCD_DisplayStr("Choose an option");
	_delay_ms(500);
	LCD_ClearScreen();
	LCD_DisplayStr("- : check in");
	LCD_GoToRowColumn(1,0);
	LCD_DisplayStr("+ : change pass");


	op = KeyPad_getPressedKey();
	_delay_ms(450);
	Takeoption(op);



	}





}

uint8 CheckPassWord(void){
	uint8 p1[4],i;
	UART_SendByte('#');
	while(UART_RecieveByte() != '#'){}
		LCD_ClearScreen();

		LCD_DisplayStr("Enter Your Pass");
		for(i = 0 ; i <4 ;i++){
			p1[i] = KeyPad_getPressedKey();
			_delay_ms(450);
			LCD_GoToRowColumn(1,i);
			LCD_DisplayChar('*');
		}
		for(i = 0 ; i <4 ;i++){
			UART_SendByte(p1[i]);
			while(UART_RecieveByte() != '#'){}
		}
		return (UART_RecieveByte());
}

uint8 SetNewPassWord(void){
	uint8 p1[4],i;
	UART_SendByte('*');
	while(UART_RecieveByte() != '*'){}
	LCD_ClearScreen();

	LCD_DisplayStr("Enter New Pass");
	for(i = 0 ; i <4 ;i++){
		p1[i] = KeyPad_getPressedKey();
		_delay_ms(450);
		LCD_GoToRowColumn(1,i);
		LCD_DisplayChar('*');
	}
	for(i = 0 ; i <4 ;i++){
			UART_SendByte(p1[i]);
			while(UART_RecieveByte() != '*'){}
		}
	LCD_ClearScreen();

	UART_SendByte('*');
	LCD_DisplayStr("Renter The Pass");
	for(i = 0 ; i <4 ;i++){
		p1[i] = KeyPad_getPressedKey();
		_delay_ms(450);
		LCD_GoToRowColumn(1,i);
		LCD_DisplayChar('*');
	}
	for(i = 0 ; i <4 ;i++){
			UART_SendByte(p1[i]);
			while(UART_RecieveByte() != '*'){}
		}
	return (UART_RecieveByte());
}
void Takeoption(uint8 op){
	if(op =='+'){
		uint8 i ;
		LCD_ClearScreen();
		LCD_DisplayStr("Change password");
		_delay_ms(500);
		for(i=0 ; i<3;i++){
		if(CheckPassWord()==1){
			UART_SendByte('*');
			while(SetNewPassWord() == 0){};
			break;
		}
		else{
			LCD_ClearScreen();
						LCD_DisplayStr("wrong password");
						if(i==2){
						UART_SendByte('#');
						TIMER_Start(1024,15624);}
						else{UART_SendByte('*');
						TIMER_Start(1024,3906);}


						while(FLAG==0){};
						FLAG=0;
						LCD_ClearScreen();
		}
		}
	}
	else if(op =='-'){
		uint8 i =0;
		LCD_ClearScreen();
		LCD_DisplayStr("Enter the room");
		_delay_ms(500);
		for(i=0 ; i<3;i++){
		if(CheckPassWord()==1){
			LCD_ClearScreen();
			UART_SendByte('#');
			LCD_DisplayStr("opening the door");

			TIMER_Start(1024,46872);
			while(FLAG==0){};
			FLAG=0;
			LCD_ClearScreen();
			LCD_DisplayStr("Closing the door");
			TIMER_Start(1024,31248);
			while(FLAG==0){};
			FLAG=0;
			LCD_ClearScreen();
			break;

		}
		else{
			LCD_ClearScreen();
			LCD_DisplayStr("wrong password");
			if(i==2){
			UART_SendByte('#');
			TIMER_Start(1024,15624);}
			else{UART_SendByte('*');
			TIMER_Start(1024,3906);}


			while(FLAG==0){};
			FLAG=0;
			LCD_ClearScreen();
		}
		}
	}

}


