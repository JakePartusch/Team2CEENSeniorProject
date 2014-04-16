#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART.h"
USART usart = USART(1, 103);
int main (void)
{
	TIMSK1 |= (1 << TOIE1 ); // Enable overflow interrupt
	sei () ; // Enable global interrupts
	TCNT1 = 910; // Preload timer with precalculated value
	TCCR1B = 0;
	while(1)
	{
	}
}
ISR ( TIMER1_OVF_vect )
{
	usart.transmit_Str("Jake");
	TCNT1 = 49910;
}