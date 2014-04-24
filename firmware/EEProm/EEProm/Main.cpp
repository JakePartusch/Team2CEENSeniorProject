#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "USART.h"
#include "EEProm.h"


int main(void)
{
	USART usart = USART(0,103);
	//uint8_t message[] ="Write to EEPROM";
	EEProm eeprom = EEProm();
	eeprom.setBaud("9600"); //stores the address?
	eeprom.setAttenuation("100 dbm");
	eeprom.setId("123ABC");
	eeprom.setPower("1 W");
	char baud[10];
	char attenuation[10];
	char id[10];
	char power[10];
	eeprom.getBaud(baud);//breaks the USART?
	eeprom.getAttenuation(attenuation);
	eeprom.getId(id);
	eeprom.getPower(power);	

	while(1)
	{
		usart.transmit_Str(baud);
		usart.transmit_Str(attenuation);
		usart.transmit_Str(id);
		usart.transmit_Str(power);
		_delay_ms(1000);
	}
}