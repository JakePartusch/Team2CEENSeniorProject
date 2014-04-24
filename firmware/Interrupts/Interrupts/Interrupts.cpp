/*
 * Interrupts.cpp
 *
 * Created: 3/27/2014 2:12:48 PM
 *  Author: Jake
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../../lcd/USART.h"

USART usart = USART(0, 103);
int main(void)
{
	USART usart = USART(0, 103);
	sei();
	PCMSK0 |= (1<<PCINT5);
	PCMSK0 |= (1<<PCINT6);
	PCMSK0 |= (1<<PCINT7);
	PCICR |= (1<< PCIE0);
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}

ISR(PCINT0_vect) {
	if(!(PINA & (1<<PINA5)))
	{
		usart.transmit('j');
	}
	if(!(PINA & (1<<PINA6)))
	{
		usart.transmit('k');
	}
	if(!(PINA & (1<<PINA7)))
	{
		usart.transmit('l');
	}
	
	_delay_ms(100); 
}