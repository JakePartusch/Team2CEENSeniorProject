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
#include <stdlib.h>

USART usart0 = USART(0, 103);
uint16_t timerCounter =0;
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
	if(timerCounter == 10) {
		usart0.transmit_Str("NODE=1&PORT=1&ATTEN=-102&PORT=2&ATTEN=-90&PORT=&ATTEN=\n");
		timerCounter = 0;
	}
	timerCounter++;
	TCNT1 = 49910;
}