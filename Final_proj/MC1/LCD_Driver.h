/*
 * LCD_Driver.h
 *
 *  Created on: Sep 21, 2020
 *      Author: ahmed
 */

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

#include "common_macros.h"
#include "micro_config.h"
#include "std_types.h"

/* LCD pins */

#define RS PB1
#define RW PB2
#define E  PB3
#define LCD_CTRL_PORT PORTB
#define LCD_CTRL_PORT_DIR DDRB

#define LCD_DATA_PORT PORTC
#define LCD_DATA_PORT_DIR DDRC

/* LCD commands */

#define CLEAR_COMMAND 0x01
#define LCD_MODE 0x38
#define CURSOR_OFF 0x0c
#define CURSOR_ON 0x0e
#define SET_CURSOR_LOCATION 0x80

/* functions prototypes */

void LCD_Init(void);
void LCD_SendCommand(uint8 command);
void LCD_DisplayChar(uint8 data);
void LCD_DisplayStr(const char *str);
void LCD_ClearScreen(void);
void LCD_DisplayStrRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_GoToRowColumn(uint8 row,uint8 col);
void LCD_IntgerToString(int data);





#endif /* LCD_DRIVER_H_ */
