#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART.h"
#define F_CPU 16000000UL
#include <util/delay.h>

USART usart = USART(0, 103);
int main(void)
{
	UCSR0B |= (1 << RXCIE0 );
	sei ();
    while(1)
    {
        //usart.transmit_Str("Jake\n");
		//_delay_ms(100); 
    }
}

ISR (USART0_RX_vect)
{
	char ReceivedByte ;
	ReceivedByte = UDR0; // Fetch the received byte value into the variable " ByteReceived "
	usart.transmit(ReceivedByte);
}