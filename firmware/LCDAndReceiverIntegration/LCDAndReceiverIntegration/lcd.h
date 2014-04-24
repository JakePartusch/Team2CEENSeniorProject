#include "Screen.h"
#include "Receiver.h"
class LCD
{
	private:
		int getSelectedIndex();
		Screen buildHomeScreen();
		Screen buildPort1Screen();
		Screen buildPort2Screen();
		Screen buildPort3Screen();
		Field homeFields[4];
		Field port1Fields[4];
		Field port2Fields[4];
		Field port3Fields[4];
		Screen homeScreen;
		Screen port1Screen;
		Screen port2Screen;
		Screen port3Screen;
		Receiver *receivers;
		int currentScreen;
		void init();
		void drawScreen(int screen);
		void clearScreen(bool onlyFields);
	public:
		LCD(Receiver *receivers);
		void moveSelectedUp();
		void moveSelectedDown();		
		void refresh();
		void select();
		LCD();
};