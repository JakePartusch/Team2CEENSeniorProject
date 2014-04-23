#include <avr/io.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"
#include "lcd.h"

LCD::LCD() {
	
}

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
	if(currentScreen == 0) {
		bool onlyFields = true;
		clearScreen(onlyFields);
		homeScreen = buildHomeScreen();
		drawScreen(0);
	}
}
void LCD::init()
{
	homeScreen = buildHomeScreen();
	port1Screen = buildPort1Screen();
	port2Screen = buildPort2Screen();
	port3Screen = buildPort3Screen();
	drawScreen(0);
}

void LCD::select() {
	int index = getSelectedIndex();
	if(currentScreen == 0) {
		switch (index) {
			case 1:
				clearScreen(false);
				port1Screen = buildPort1Screen();
				drawScreen(1);
				break;
			case 2:
				clearScreen(false);
				port2Screen = buildPort2Screen();
				drawScreen(2);
				break;
			case 3:
				clearScreen(false);
				port3Screen = buildPort3Screen();
				drawScreen(3);
				break;
		}
	}
	else {
		switch (index) {
			case 1:
				break;
			case 2:
				break;
			case 3:
				clearScreen(false);
				drawScreen(0);
				break;
		}
	}
}

void LCD::clearScreen(bool onlyFields) {
	switch(currentScreen) {
		case 0:
			homeScreen.clearScreen(onlyFields);
			break;
		case 1:
			port1Screen.clearScreen(onlyFields);
			break;
		case 2:
			port2Screen.clearScreen(onlyFields);
			break;
		case 3:
			port3Screen.clearScreen(onlyFields);
			break;
	}
}

void LCD::moveSelectedDown() {
	switch(currentScreen) {
		case 0:
			homeScreen.moveSelectedDown();
			break;
		case 1:
			port1Screen.moveSelectedDown();
			break;
		case 2:
			port2Screen.moveSelectedDown();
			break;
		case 3:
			port3Screen.moveSelectedDown();
			break;
	}
}

void LCD::moveSelectedUp() {
	switch(currentScreen) {
		case 0:
			homeScreen.moveSelectedUp();
			break;
		case 1:
			port1Screen.moveSelectedUp();
			break;
		case 2:
			port2Screen.moveSelectedUp();
			break;
		case 3:
			port3Screen.moveSelectedUp();
			break;
	}
}

int LCD::getSelectedIndex() {
	int index = 0;
	switch(currentScreen) {
		case 0:
			index = homeScreen.getSelectedIndex();
			break;
		case 1:
			index = port1Screen.getSelectedIndex();
			break;
		case 2:
			index = port2Screen.getSelectedIndex();
			break;
		case 3:
			index = port3Screen.getSelectedIndex();
			break;
	}
	return index;
}

void LCD::drawScreen(int screen) {
	switch(screen) {
		case 0:
			homeScreen.drawScreen();
			currentScreen = 0;
			break;
		case 1:
			port1Screen.drawScreen();
			currentScreen = 1;
			break;
		case 2:
			port2Screen.drawScreen();
			currentScreen = 2;
			break;
		case 3:
			port3Screen.drawScreen();
			currentScreen = 3;
			break;
	}
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

Screen LCD::buildPort1Screen()
{
	port1Fields[1] = Field("SN:", (char *) receivers[0].serialNumber);
	port1Fields[2] = Field("Current:",(char *) receivers[0].attenuation);
	port1Fields[3] = Field("Back");
	Screen screen("Port 1", 4);
	screen.fields = port1Fields;
	return screen;
}

Screen LCD::buildPort2Screen()
{
	port2Fields[1] = Field("SN:", (char *) receivers[1].serialNumber);
	port2Fields[2] = Field("Current:",(char *) receivers[1].attenuation);
	port2Fields[3] = Field("Back");
	Screen screen("Port 2", 4);
	screen.fields = port2Fields;
	return screen;
}

Screen LCD::buildPort3Screen()
{
	port3Fields[1] = Field("SN:", (char *) receivers[2].serialNumber);
	port3Fields[2] = Field("Current:",(char *) receivers[2].attenuation);
	port3Fields[3] = Field("Back");
	Screen screen("Port 3", 4);
	screen.fields = port3Fields;
	return screen;
}