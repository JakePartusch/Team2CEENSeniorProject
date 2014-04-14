#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "Multiplexer.h"
#include "USART.h"
void testCase(const char array[]);

Multiplexer multiplexer = Multiplexer();
USART usart = USART(1, 103);
char receiverData[200];
int main(void)
{
	UCSR1B |= (1 << RXCIE1 );
	sei ();
    while(1)
    {
		multiplexer.incrementPort();
		/*testCase("REC=0x003333&-102&1397187777\n");
		_delay_ms(400);*/
		multiplexer.getReceiversString(receiverData);
		usart.transmit_Str(receiverData);
		_delay_ms(400);
	}
}

void testCase(const char array[]) {
	int i = 0;
	while(array[i] != 0) {
		multiplexer.addToBuffer(array[i]);
		i++;
	}
}

ISR (USART1_RX_vect)
{
	char receivedByte ;
	receivedByte = UDR1; // Fetch the received byte value into the variable " ByteReceived "
	//usart.transmit(receivedByte);
	multiplexer.addToBuffer(receivedByte);
}