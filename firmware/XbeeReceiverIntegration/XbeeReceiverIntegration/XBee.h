#include "USART.h"
class XBee
{
	private:
		USART usart;
		bool isOK();
		void sendCommand(char *command);
		void setCommandMode();
	public:
		XBee();
		void send(char *data);
		void init(USART usart);
};