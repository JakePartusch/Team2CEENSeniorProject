#define BACKGROUND_COLOR 0x001F
#define TEXT_COLOR 0xFFFF
class Field
{
	public:
		int xCoordinate;
		int yCoordinate;
		char *description;
		bool isSelected;
		int selectedX;
		int selectedY;
		Field();
		Field(char *description);
};

class Screen
{
	private:
		int getSelectedIndex();
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
	public:
		char *title;
		int xTitle;
		int yTitle;
		int titleSize;
		Field *fields;
		int fieldLength;
		Screen(char *title, int fieldLength);
		void drawScreen();
		void moveSelectedDown();
		void begin();
		void clearScreen();
};