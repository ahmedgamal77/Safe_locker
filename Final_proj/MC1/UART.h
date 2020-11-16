/*
 * UART.h
 *
 *  Created on: Oct 2, 2020
 *      Author: ahmed
 */

#ifndef UART_H_
#define UART_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"
struct UART_init{
	uint8 parity_mode; /*  0 : disabled
					       1 : enabled even parity
					       2 : enabled odd parity */
	uint8 char_size;
	uint8 stop_bit; /* 0 : one bit
					  1 : two bits */
	uint16 baud_rate;



};
void UART_Init(struct UART_init *i);

void UART_SendByte(const uint8 data);

uint8 UART_RecieveByte(void);

void UART_SendString(const uint8 *Str);

void UART_ReceiveString(uint8 *Str);

#endif /* UART_H_ */
