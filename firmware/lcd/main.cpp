#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "lcd.h"
#include "../EEProm/EEProm/USART.h"


int main(void)
{
	EEProm eeProm = EEProm();
	USART usart = USART(0, 103);
	eeProm.setAttenuation("100");
	LCD lcd = LCD(eeProm);
	_delay_ms(1000);
	char attenuation[10];
	eeProm.setAttenuation("99");
	eeProm.getAttenuation(attenuation);
	lcd.refresh();
	while(1)
	{
		usart.transmit_Str(attenuation);
		_delay_ms(100);
	}
}