/*
 * UART.c
 *
 *  Created on: Oct 2, 2020
 *      Author: ahmed
 */

#include "UART.h"

void UART_Init(struct UART_init *i ){
	SET_BIT(UCSRA,U2X);
	UCSRB = (1<<RXEN) | (1<<TXEN);
	CLEAR_BIT(UCSRC,UMSEL);

	/* parity mode */
	if((*i).parity_mode==0){CLEAR_BIT(UCSRC,UPM0);
	CLEAR_BIT(UCSRC,UPM1);}
	else if((*i).parity_mode==1){CLEAR_BIT(UCSRC,UPM0);
	SET_BIT(UCSRC,UPM1);}
	else if((*i).parity_mode==2){SET_BIT(UCSRC,UPM0);
		SET_BIT(UCSRC,UPM1);}

	/* stop bit */
	if(i->stop_bit==0){CLEAR_BIT(UCSRC,USBS);}
	else if(i->stop_bit==1){SET_BIT(UCSRC,USBS);}

	/* character size */
	if(i->char_size == 5 ){CLEAR_BIT(UCSRC,UCSZ0);
	CLEAR_BIT(UCSRC,UCSZ1); CLEAR_BIT(UCSRC,UCSZ2);}
	else if(i->char_size == 6 ){SET_BIT(UCSRC,UCSZ0);
	CLEAR_BIT(UCSRC,UCSZ1); CLEAR_BIT(UCSRC,UCSZ2);}
	else if(i->char_size == 7 ){CLEAR_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1); CLEAR_BIT(UCSRC,UCSZ2);}
	else if(i->char_size == 8 ){SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1); CLEAR_BIT(UCSRC,UCSZ2);}
	else if(i->char_size == 9 ){SET_BIT(UCSRC,UCSZ0);
	SET_BIT(UCSRC,UCSZ1); SET_BIT(UCSRC,UCSZ2);}
	uint16 b = (((F_CPU / (i->baud_rate* 8UL))) - 1);
	UBRRH = b>>8;
	UBRRL = b;


}


void UART_SendByte(const uint8 data)
{
	/* UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}
	/* Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now */
	UDR = data;
	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transimission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	*******************************************************************/
}

uint8 UART_RecieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this
	 * flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	/* Read the received data from the Rx buffer (UDR) and the RXC flag
	   will be cleared after read this data */
    return UDR;
}

void UART_SendString(const uint8 *Str)
{
	uint8 i = 0;
	while(Str[i] != '\0')
	{
		UART_SendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}
	*******************************************************************/
}

void UART_ReceiveString(uint8 *Str)
{
	uint8 i = 0;
	Str[i] = UART_RecieveByte();
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_RecieveByte();
	}
	Str[i] = '\0';
}
