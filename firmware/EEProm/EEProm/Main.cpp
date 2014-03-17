#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "EEProm.h"
#include "USART.h"
int main(void)
{
	EEProm eeprom = EEProm();
	USART usart = USART(0, 103);
	eeprom.setBaud(1234);
	while(1)
	{
		usart.transmit_Int(eeprom.getBaud());
		_delay_ms(100);
	}
}