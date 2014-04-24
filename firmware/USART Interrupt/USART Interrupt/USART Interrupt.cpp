#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART.h"
#define F_CPU 16000000UL
#include <util/delay.h>

USART usart = USART(1, 103);
int main(void)
{
	UCSR1B |= (1 << RXCIE1 );
	sei ();
    while(1)
    {
        //usart.transmit_Str("Jake\n");
		//_delay_ms(100); 
    }
}

ISR (USART1_RX_vect)
{
	char ReceivedByte ;
	ReceivedByte = UDR1; // Fetch the received byte value into the variable " ByteReceived "
	usart.transmit(ReceivedByte);
}