#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "XBee.h"

XBee::XBee(void){

}
void XBee::init(USART usart)
{
	_delay_ms(1000);

	setCommandMode();
	sendCommand("atre");
	sendCommand("atmy 2");
	sendCommand("atid 3111");
	sendCommand("atdh 0");
	sendCommand("atdl 1");
	sendCommand("atwr");		
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
