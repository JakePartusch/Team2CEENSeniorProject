#include "Screen.h"
#include "../EEProm/EEProm/EEProm.h"
class LCD
{
	private:
		Screen buildTransmitterScreen();
		Screen buildReceiverScreen();
		Screen buildHomeScreen();
		Screen buildMenuScreen();
		Field receiverFields[4];
		Field transmitterFields[4];
		Field menuFields[4];
		Field homeFields[3];
		Screen homeScreen;
		Screen menuScreen;
		Screen receiverScreen;
		Screen transmitterScreen;
		EEProm eeProm;
		char attenuation[10];
		void init();
	public:
		LCD(EEProm eeProm);
		Screen currentScreen;
		void refresh();
};