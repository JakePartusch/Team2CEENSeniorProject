#include "Screen.h"
#include "lcd.h"
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
int main(void)
{
	LCD lcd = LCD();
	Screen receiverScreen = lcd.buildReceiverScreen();
	Screen transmitterScreen = lcd.buildTransmitterScreen();
	Screen menuScreen = lcd.buildMenuScreen();
	Screen homeScreen = lcd.buildHomeScreen();
	
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