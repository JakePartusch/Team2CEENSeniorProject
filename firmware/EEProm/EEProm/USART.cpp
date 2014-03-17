#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include "USART.h"
#define F_CPU 16000000UL

USART::USART(uint16_t port, uint16_t baud )
{
	this->port = port;
	if(this->port == 1)
	{
		/* Set baud rate */
		UBRR1H = (unsigned char)(baud>>8);
		UBRR1L= (unsigned char)baud;
		/* Enable receiver and transmitter */
		UCSR1B = (1<<RXEN1)|(1<<TXEN1);
		/* Set frame format: 8data, 2stop bit */
		UCSR1C = (1<<USBS1)|(3<<UCSZ10);
	}
	else if(this->port == 0)
	{
		/* Set baud rate */
		UBRR0H = (unsigned char)(baud>>8);
		UBRR0L= (unsigned char)baud;
		/* Enable receiver and transmitter */
		UCSR0B = (1<<RXEN0)|(1<<TXEN0);
		/* Set frame format: 8data, 2stop bit */
		UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	}
	
}
void USART::transmit( unsigned char data )
{
	if(this->port == 1)
	{
		/* Wait for empty transmit buffer */
		while ( !( UCSR1A & (1<<UDRE1)) )
		{
			;
		}
		/* Put data into buffer, sends the data */
		UDR1 = data;
	}
	else if(this->port == 0)
	{
		/* Wait for empty transmit buffer */
		while ( !( UCSR0A & (1<<UDRE0)) )
		{
			;
		}
		/* Put data into buffer, sends the data */
		UDR0 = data;
	}
	
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

void USART::transmit_Int(uint16_t data)
{
	char  buf[32];
	snprintf(buf, sizeof(buf), "%d", data);
	transmit_Str(buf);
}
unsigned char USART::receive()
{
	unsigned char data;
	if(this->port == 1)
	{
		while ( !(UCSR1A & (1<<RXC1)) )
		{
			;
		}
		/* Get and return received data from buffer */
		data = UDR1;
	}
	else if(this->port == 0)
	{
		while ( !(UCSR0A & (1<<RXC0)) )
		{
			;
		}
		/* Get and return received data from buffer */
		data = UDR0;		
	}
	return data;
}
char* USART::receive_Str()
{
	char test[256] = "";
	char receivedChar = receive();
	while(receivedChar != '\n')
	{
		strncat(test, &receivedChar, 1);
		receivedChar = receive();
	}
	return test;
}
