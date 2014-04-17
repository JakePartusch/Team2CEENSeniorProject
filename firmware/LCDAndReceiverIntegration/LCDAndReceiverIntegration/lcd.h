#include "Screen.h"
#include "Receiver.h"
class LCD
{
	private:
		Screen buildHomeScreen();
		Field homeFields[4];
		Screen homeScreen;
		Receiver *receivers;
		void init();
	public:
		LCD(Receiver *receivers);
		Screen currentScreen;
		void refresh();
};