#include <avr/io.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"
#include "lcd.h"


LCD::LCD(Receiver *receivers)
{
	this->receivers = receivers;
	Screen screen = Screen();
	screen.begin();
	screen.init();
	init();
}
void LCD::refresh()
{
	homeScreen.clearScreen();
	homeScreen = buildHomeScreen();
	homeScreen.drawScreen();
}
void LCD::init()
{
	homeScreen = buildHomeScreen();
	homeScreen.drawScreen();
}

Screen LCD::buildHomeScreen()
{
	homeFields[1] = Field("Port 1:", (char *) receivers[0].attenuation);
	homeFields[2] = Field("Port 2:",(char *) receivers[1].attenuation);
	homeFields[3] = Field("Port 3:",(char *) receivers[2].attenuation);
	Screen screen("HOME", 4);
	screen.fields = homeFields;
	return screen;
}