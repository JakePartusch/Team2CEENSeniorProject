#define BACKGROUND_COLOR 0x001F
#define TEXT_COLOR 0xFFFF
class Field
{
	private:
	
	public:
		char *description;
		char *value;
		bool isSelected;
		int selectedX;
		int selectedY;
		int valueX;
		int valueY;
		int xCoordinate;
		int yCoordinate;
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
		char *title;
		int xTitle;
		int yTitle;
		int titleSize;
		int fieldLength;
	public:
		Field *fields;
		Screen(char *title, int fieldLength);
		Screen();
		void begin();
		void drawScreen();
		void moveSelectedDown();
		void clearScreen();
};