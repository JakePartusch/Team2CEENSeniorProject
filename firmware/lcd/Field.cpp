#include <avr/io.h>
#include "Field.h"
Field::Field()
{}

Field::Field(char *description)
{
	this->description = description;
	value = 0;
}
Field::Field(char *description, char *value)
{
	this->description = description;
	this->value = value;
}