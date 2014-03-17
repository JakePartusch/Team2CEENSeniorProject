#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "XBee.h"
int main(void)
{
	XBee xbee = XBee();
	xbee.init();
	while(1)
	{
		xbee.send("Jake");
		_delay_ms(10);
	}
}