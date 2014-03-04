#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"
#include "Screen.h"

Screen buildTransmitterScreen();
Screen buildReceiverScreen();
Screen buildHomeScreen();
Screen buildMenuScreen();
Field receiverFieldArray[4];
Field transmitterFieldArray[4];
Field menuFieldArray[4];
Field homeFieldArray[3];

int main(void)
{
	Screen receiverScreen = buildReceiverScreen();
	Screen transmitterScreen = buildTransmitterScreen();
	Screen menuScreen = buildMenuScreen();
	Screen homeScreen = buildHomeScreen();
	homeScreen.begin();
	homeScreen.drawScreen();
	_delay_ms(1000);
	homeScreen.clearScreen();
	menuScreen.drawScreen();
	_delay_ms(1000);
	menuScreen.clearScreen();
	transmitterScreen.drawScreen();
	_delay_ms(1000);
	menuScreen.clearScreen();
	receiverScreen.drawScreen();

}
Screen buildTransmitterScreen()
{
	transmitterFieldArray[1] = Field("Power");
	transmitterFieldArray[2] = Field("Baud");
	transmitterFieldArray[3] = Field("Back");
	Screen screen = Screen("Transmitter", 4);
	screen.fields = transmitterFieldArray;
	return screen;
}
Screen buildReceiverScreen()
{
	receiverFieldArray[1] = Field("Interval");
	receiverFieldArray[2] = Field("Baud");
	receiverFieldArray[3] = Field("Back");
	Screen screen("Receiver", 4);
	screen.fields = receiverFieldArray;
	return screen;
}

Screen buildMenuScreen()
{
	menuFieldArray[1] = Field("Transmitter");
	menuFieldArray[2] = Field("Receiver");
	menuFieldArray[3] = Field("Back");
	Screen screen("Settings", 4);
	screen.fields = menuFieldArray;
	return screen;
}
Screen buildHomeScreen()
{
	homeFieldArray[1] = Field("Current");
	homeFieldArray[2] = Field("Menu");
	Screen screen("HOME",3);
	screen.fields = homeFieldArray;
	return screen;
}