#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include "USART.h"


USART usart = USART(0, 103);
EEProm eeProm = EEProm();
LCD lcd = LCD(eeProm);
void enableInterrupts();

int main(void)
{
	
	enableInterrupts();
	eeProm.setAttenuation("100");
	
	_delay_ms(1000);
	char attenuation[10];
	eeProm.setAttenuation("99");
	eeProm.getAttenuation(attenuation);
	lcd.refresh();
	while(1)
	{
		//usart.transmit_Str(attenuation);
		//_delay_ms(100);
	}
}

void enableInterrupts()
{
	sei();
	PCMSK0 |= (1<<PCINT5);
	PCMSK0 |= (1<<PCINT6);
	PCMSK0 |= (1<<PCINT7);
	PCICR |= (1<< PCIE0);
}

ISR(PCINT0_vect) {
	if(!(PINA & (1<<PINA5)))
	{
		lcd.currentScreen.moveSelectedDown();
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