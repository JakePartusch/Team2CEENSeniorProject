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
	Field(char *description, char *value);
};