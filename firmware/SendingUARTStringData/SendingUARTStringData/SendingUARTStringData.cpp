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

int main(void)
{
	USART usart0 = USART(0, 103);
    while(1)
    {
		usart0.transmit_Str("REC=0x003333&-102&1397187777\n");
		_delay_ms(200);
    }
}