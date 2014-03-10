/*
 * EEProm.cpp
 *
 * Created: 3/10/2014 12:07:41 PM
 *  Author: Jake
 */ 


#include <avr/io.h>
#include <avr/eeprom.h>
uint8_t EEMEM NonVolatileChar ;
uint16_t EEMEM NonVolatileInt ;
uint8_t EEMEM NonVolatileString [10];

int main(void)
{
	uint8_t SRAMchar ;
	uint16_t SRAMint ;
	uint8_t SRAMstring [10];
	SRAMchar = eeprom_read_byte (& NonVolatileChar );
	SRAMint = eeprom_read_word (& NonVolatileInt );
	eeprom_read_block (( void *) SRAMstring , ( const void *) NonVolatileString , 10);
}