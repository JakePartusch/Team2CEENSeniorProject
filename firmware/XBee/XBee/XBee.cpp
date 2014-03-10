#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include "USART.h"



int main(void)
{
    while(1)
    {
        USART usart = USART(1, 103);
		
		while(1)
		{
			usart.transmit_Str("Jake\n");
			_delay_ms(500);
		}
    }
}

