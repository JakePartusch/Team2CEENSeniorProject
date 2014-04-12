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
	USART usart1 = USART(1, 103);
    while(1)
    {
		//REC=0x001369&-102&1397187777
        usart0.transmit_Str("REC=0x001369&-102&1397188888");
		_delay_ms(300);
		usart1.transmit_Str("REC=0x009&-95&1397189999");
		_delay_ms(200);
    }
}