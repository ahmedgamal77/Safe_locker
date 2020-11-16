/*
 * LCD_Driver.c
 *
 *  Created on: Sep 21, 2020
 *      Author: ahmed
 */
#include "LCD_Driver.h"

void LCD_Init(void){
	LCD_DATA_PORT_DIR = 0xFF; /* Configure the data port as output port */
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW); /* Configure the control pins(E,RS,RW) as output pins */
	LCD_SendCommand(LCD_MODE);
	LCD_SendCommand(CURSOR_OFF);
	LCD_SendCommand(CLEAR_COMMAND);



}
void LCD_SendCommand(uint8 command){
	CLEAR_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	LCD_DATA_PORT = command ;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
}
void LCD_DisplayChar(uint8 data){

	SET_BIT(LCD_CTRL_PORT,RS);
	CLEAR_BIT(LCD_CTRL_PORT,RW);
	_delay_ms(1);
	SET_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
	LCD_DATA_PORT = data ;
	_delay_ms(1);
	CLEAR_BIT(LCD_CTRL_PORT,E);
	_delay_ms(1);
}

void LCD_DisplayStr(const char* str){
	uint8 i = 0 ;
	while(str[i] != '\0'){
		LCD_DisplayChar(str[i]);
		i++;
	}
}
void LCD_ClearScreen(void){
	LCD_SendCommand(CLEAR_COMMAND);

}
void LCD_GoToRowColumn(uint8 row, uint8 col){
	uint8 Address;

		/* first of all calculate the required address */
		switch(row)
		{
			case 0:
					Address=col;
					break;
			case 1:
					Address=col+0x40;
					break;
			case 2:
					Address=col+0x10;
					break;
			case 3:
					Address=col+0x50;
					break;
		}
		/* to write to a specific address in the LCD
		 * we need to apply the corresponding command 0b10000000+Address */
		LCD_SendCommand(Address | SET_CURSOR_LOCATION);
}
void LCD_DisplayStrRowColumn(uint8 row,uint8 col,const char *Str){
	LCD_GoToRowColumn(row,col);
	LCD_DisplayStr(Str);
}
void LCD_IntgerToString(int data){
	char buff[16]; /* String to hold the ascii result */
	itoa(data,buff,10); /* 10 for decimal */
	LCD_DisplayStr(buff);


}

