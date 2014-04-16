#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include "USART.h"
#define F_CPU 16000000UL

USART::USART() {	
}
void USART::init(uint16_t baud) {
	/* Set baud rate */
	UBRR1H = (unsigned char)(baud>>8);
	UBRR1L= (unsigned char)baud;
	/* Enable receiver and Receive interrupt */
	UCSR1B = (1<<RXEN1)|(1<<RXCIE1);
	/* Set frame format: 8data, 2stop bit */
	UCSR1C = (1<<USBS1)|(3<<UCSZ10);

	/* Set baud rate */
	UBRR0H = (unsigned char)(baud>>8);
	UBRR0L= (unsigned char)baud;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	
}
void USART::transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	{
		;
	}
	/* Put data into buffer, sends the data */
	UDR0 = data;
}
void USART::transmit_Str(char *data)
{
	unsigned char i = 0;
	while(data[i] != 0)
	{
		transmit(data[i]);
		i++;
	}
}


