#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "Screen.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"

#define _cs 7
#define _dc 5
#define _rst 6
Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);

#define min(a,b) \
({ __typeof__ (a) _a = (a); \
	__typeof__ (b) _b = (b); \
_a < _b ? _a : _b; })


Screen::Screen()
{}
Screen::Screen(char *title, int fieldLength)
{
	this->title = title;
	this->fieldLength = fieldLength;
}
void Screen::begin()
{
	tft.begin();
}
void Screen::init() {
	tft.fillScreen(ILI9340_BLACK);
	drawBackground();
}
void Screen::drawScreen()
{
	drawTitle();
	drawFields();
}

void Screen::drawTitle()
{
	yTitle = 10;
	xTitle = 50 - ((strlen(title)-5)*10);
	titleSize = 5;
	if(strlen(title) > 7)
	{
		titleSize = 4;
	}
	if(strlen(title) > 9)
	{
		titleSize = 3;
		xTitle = 30;
	}
	printText(title, titleSize, xTitle, yTitle);
	drawUnderline();
}
void Screen::drawUnderline()
{
	int x = 0;
	int y = yTitle + (10*titleSize);
	int width = tft.width();
	int height = 5;
	tft.fillRect(x, y, width, height, TEXT_COLOR);
}
void Screen::drawFields()
{
	for(int i = 1; i < fieldLength; i++)
	{
		fields[i].xCoordinate = 20;
		fields[i].yCoordinate = (tft.height()/(fieldLength))*i;
		if(i == 1)
		{
			selectField(i);
		}
		char str[80];
		str[0] = 0; 
		strcat (str, fields[i].description);
		strcat (str, " ");
		strcat (str, fields[i].value);
		
		printText(str, 3, fields[i].xCoordinate, fields[i].yCoordinate);
	}
}

int Screen::getSelectedIndex()
{
	for(int i = 1; i < fieldLength; i++)
	{
		if(fields[i].isSelected)
		{
			return i;
		}
	}
	return 0;
}

void Screen::moveSelectedDown()
{
	int index = getSelectedIndex();
	unselectField(index);
	index++;
	if(index == fieldLength)
	{
		index = 1;
	}
	selectField(index);
}

void Screen::moveSelectedUp()
{
	int index = getSelectedIndex();
	unselectField(index);
	index--;
	if(index == 0)
	{
		index = fieldLength -1;
	}
	selectField(index);
}

void Screen::selectField(int index)
{
	fields[index].selectedX = fields[index].xCoordinate - 15;
	fields[index].selectedY = fields[index].yCoordinate + 5;
	fields[index].isSelected = true;
	drawRectanglePointer(fields[index].selectedX, fields[index].selectedY);
}

void Screen::unselectField(int index)
{
	fields[index].isSelected = false;
	eraseRectanglePointer(fields[index].selectedX, fields[index].selectedY);
}
void Screen::printText(char *c, int size, int x, int y)
{
	tft.setTextSize(size);
	for(int i = 0; i < strlen(c); i++)
	{
		tft.setCursor(x + i*(size * 6), y);
		tft.write(c[i]);
	}
}
void Screen::drawRectanglePointer(int x, int y) {
	int width = 10;
	int height = 10;
	tft.fillRect(x, y, width, height, TEXT_COLOR);
}
void Screen::eraseRectanglePointer(int x, int y) {
	int width = 10;
	int height = 10;
	tft.fillRect(x, y, width, height, BACKGROUND_COLOR);
}
void Screen::drawBackground()
{
	int i= min(tft.width(), tft.height());
	tft.fillRoundRect(0, 0, tft.width(), tft.height(), i/8, BACKGROUND_COLOR);
}
void Screen::clearScreen(bool onlyValue)
{
	if(!onlyValue) {
		eraseTitle();
		eraseFields();
	}
	else {
		eraseValues();
	}
}
void Screen::eraseValues() {
	for(int i = 1; i < 4; i++)
	{
		int x = 135;
		int y = fields[i].yCoordinate;
		int width = tft.width();
		int height = 25;
		tft.fillRect(x, y, width, height, BACKGROUND_COLOR);
	}
}
void Screen::eraseFields()
{
	for(int i = 1; i < 4; i++)
	{
		int x = 0;
		int y = fields[i].yCoordinate;
		int width = tft.width();
		int height = 25;
		tft.fillRect(x, y, width, height, BACKGROUND_COLOR);
	}
}
void Screen::eraseTitle()
{
	int x = 0;
	int y = yTitle;
	int width = tft.width();
	int height = (titleSize*10)+ 5;
	tft.fillRect(x, y, width, height, BACKGROUND_COLOR);
}