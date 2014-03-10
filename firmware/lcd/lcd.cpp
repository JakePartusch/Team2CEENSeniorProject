#include <avr/io.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"
#include "Screen.h"
#include "lcd.h"

LCD::LCD()
{
	Screen screen = Screen();
	screen.begin();
}
Screen LCD::buildTransmitterScreen()
{
	transmitterFields[1] = Field("Power");
	transmitterFields[2] = Field("Baud");
	transmitterFields[3] = Field("Back");
	Screen screen = Screen("Transmitter", 4);
	screen.fields = transmitterFields;
	return screen;
}
Screen LCD::buildReceiverScreen()
{
	receiverFields[1] = Field("Interval");
	receiverFields[2] = Field("Baud");
	receiverFields[3] = Field("Back");
	Screen screen("Receiver", 4);
	screen.fields = receiverFields;
	return screen;
}

Screen LCD::buildMenuScreen()
{
	menuFields[1] = Field("Transmitter");
	menuFields[2] = Field("Receiver");
	menuFields[3] = Field("Back");
	Screen screen("Settings", 4);
	screen.fields = menuFields;
	return screen;
}
Screen LCD::buildHomeScreen()
{
	homeFields[1] = Field("Current");
	homeFields[2] = Field("Menu");
	Screen screen("HOME",3);
	screen.fields = homeFields;
	return screen;
}