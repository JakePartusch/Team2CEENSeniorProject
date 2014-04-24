#define BACKGROUND_COLOR 0x001F
#define TEXT_COLOR 0xFFFF
#include "Field.h"
class Screen
{
	private:
		void unselectField(int index);
		void selectField(int index);
		void printText(char *c, int size, int x, int y);
		void drawRectanglePointer(int x, int y);
		void eraseRectanglePointer(int x, int y);
		void drawBackground();
		void drawUnderline();
		void drawTitle();
		void drawFields();
		void eraseFields();
		void eraseTitle();
		void eraseValues();
		int xTitle;
		int yTitle;
		int titleSize;
		int fieldLength;
	public:
		char *title;
		Field *fields;
		Screen(char *title, int fieldLength);
		Screen();
		void begin();
		void drawScreen();
		void moveSelectedDown();
		void moveSelectedUp();
		void clearScreen(bool onlyValue);
		void init();
		int getSelectedIndex();
};