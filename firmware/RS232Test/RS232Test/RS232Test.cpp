#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "Multiplexer.h"
void testCase(const char array[]);

Multiplexer multiplexer = Multiplexer();
int main(void)
{
	sei ();
    while(1)
    {
		multiplexer.incrementPort();
		_delay_ms(400);
		testCase("REC=0x001111&-102&1397187777\n");
		_delay_ms(400);
		testCase("REC=0x002222&-102&1397187777\n");
		_delay_ms(400);
		testCase("REC=0x003333&-102&1397187777\n");
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
	multiplexer.addToBuffer(receivedByte);
}