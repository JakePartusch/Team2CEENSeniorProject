#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "Screen.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"

#define _cs 0
#define _dc 2
#define _rst 1
Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);

#define min(a,b) \
({ __typeof__ (a) _a = (a); \
	__typeof__ (b) _b = (b); \
_a < _b ? _a : _b; })
Field::Field()
{}

Field::Field(char *description)
{
	this->description = description;
}

Screen::Screen(char *title, int fieldLength)
{
	this->title = title;
	this->fieldLength = fieldLength;
}
void Screen::begin()
{
	tft.begin();
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
	this->yTitle = 10;
	this->xTitle = 50 - ((strlen(this->title)-5)*10);
	this->titleSize = 5;
	if(strlen(this->title) > 7)
	{
		this->titleSize = 4;
	}
	if(strlen(this->title) > 9)
	{
		this->titleSize = 3;
		this->xTitle = 30;
	}
	printText(this->title, this->titleSize, this->xTitle, this->yTitle);
	drawUnderline();
}
void Screen::drawUnderline()
{
	int x = 0;
	int y = yTitle + (10*this->titleSize);
	int width = tft.width();
	int height = 5;
	tft.fillRect(x, y, width, height, TEXT_COLOR);
}
void Screen::drawFields()
{
	for(int i = 1; i < this->fieldLength; i++)
	{
		this->fields[i].xCoordinate = 20;
		this->fields[i].yCoordinate = (tft.height()/(fieldLength))*i;
		if(i == 1)
		{
			selectField(i);
		}
		printText(this->fields[i].description, 3, this->fields[i].xCoordinate, this->fields[i].yCoordinate);
	}
}

int Screen::getSelectedIndex()
{
	for(int i = 1; i < this->fieldLength; i++)
	{
		if(this->fields[i].isSelected)
		{
			return i;
		}
	}
}

void Screen::moveSelectedDown()
{
	int index = getSelectedIndex();
	unselectField(index);
	index++;
	if(index == this->fieldLength)
	{
		index = 1;
	}
	selectField(index);
}

void Screen::selectField(int index)
{
	this->fields[index].selectedX = this->fields[index].xCoordinate - 15;
	this->fields[index].selectedY = this->fields[index].yCoordinate + 5;
	this->fields[index].isSelected = true;
	drawRectanglePointer(this->fields[index].selectedX, this->fields[index].selectedY);
}

void Screen::unselectField(int index)
{
	this->fields[index].isSelected = false;
	eraseRectanglePointer(this->fields[index].selectedX, this->fields[index].selectedY);
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
void Screen::clearScreen()
{
	eraseTitle();
	eraseFields();
}
void Screen::eraseFields()
{
	for(int i = 1; i < fieldLength; i++)
	{
		this->fields[i];
		int x = this->fields[i].xCoordinate;
		if(this->fields[i].isSelected)
		{
			x = this->fields[i].selectedX;
		}
		int y = this->fields[i].yCoordinate;
		int width = tft.width();
		int height = 25;
		tft.fillRect(x, y, width, height, BACKGROUND_COLOR);
	}
}
void Screen::eraseTitle()
{
	int x = 0;
	int y = this->yTitle;
	int width = tft.width();
	int height = (this->titleSize*10)+ 5;
	tft.fillRect(x, y, width, height, BACKGROUND_COLOR);
}