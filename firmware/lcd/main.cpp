#include "lcd.h"
#include <avr/io.h>

int main(void)
{
	EEProm eeProm = EEProm();
	LCD lcd = LCD(eeProm);
	while(1)
	{}
}