/*
 * SendingUARTStringData.cpp
 *
 * Created: 4/11/2014 4:55:03 PM
 *  Author: Jake
 */ 


#include <avr/io.h>
#include "USART.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

USART usart0 = USART(0, 103);
int main(void)
{
	
	TIMSK1 |= (1 << TOIE1 ); // Enable overflow interrupt
	sei () ; // Enable global interrupts
	TCNT1 = 49910; // Preload timer with precalculated value
	TCCR1B |= ((1 << CS02));
    while(1)
    {
    }
}
ISR ( TIMER1_OVF_vect )
{
	usart0.transmit_Str("REC=0x003333&-102&1397187777\n");
	TCNT1 = 49910;
}