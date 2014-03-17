#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "XBee.h"

XBee::XBee(void)
{
	this->usart = USART(0, 103);
}
void XBee::init(void)
{
	_delay_ms(1000);

	setCommandMode();
	sendCommand("atre");
	sendCommand("atmy 3");
	sendCommand("atid 3001");
	sendCommand("atdh 0");
	sendCommand("atdl 1");
	sendCommand("atwr");
	sendCommand("atcn");
		
}
void XBee::send(char *data)
{
	this->usart.transmit_Str(data);
}
void XBee::setCommandMode()
{
	this->usart.transmit_Str("+++");
	isOK();
}
void XBee::sendCommand(char *command)
{
	this->usart.transmit_Str(command);
	this->usart.transmit('\r');
	isOK();
}
bool XBee::isOK()
{
	if(this->usart.receive() == 'O')
	{
		if(this->usart.receive() == 'K')
		{
			if(this->usart.receive() == '\r')
			{
				return true;
			}
		}
	}
	return false;
}
