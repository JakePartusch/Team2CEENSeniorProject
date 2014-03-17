#include "USART.h"
class XBee
{
	private:
		USART usart = USART(1,103);
		bool isOK();
		void sendCommand(char *command);
		void setCommandMode();
	public:
		XBee();
		void send(char *data);
		void init(void);
};