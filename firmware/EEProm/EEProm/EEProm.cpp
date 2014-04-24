/*
 * EEProm.cpp
 *
 * Created: 3/10/2014 12:07:41 PM
 *  Author: Jake
 */ 
#include <avr/io.h>
#include <avr/eeprom.h>
#include "EEProm.h"
#include "USART.h"
uint16_t EEMEM NonVolatileAttenuation[10];
uint16_t EEMEM NonVolatileBaud[10];
uint16_t EEMEM NonVolatilePower[10];
uint16_t EEMEM NonvolatileId[10];

EEProm::EEProm()
{}

void EEProm::getBaud(char baud[])
{
	uint8_t temp [10];
	eeprom_read_block (( void *) temp , ( const void *) NonVolatileBaud , 10);
	for (int i = 0 ; i < 10 ; ++i)
	{
		baud[i] = temp[i];
	}
}
void EEProm::setBaud(char *baud)
{
	eeprom_update_block (( const void *) baud , (void *)NonVolatileBaud, 10);
}
void EEProm::getAttenuation(char attenuation[])
{
	uint8_t temp[10];
	eeprom_read_block (( void *) temp , ( const void *) NonVolatileAttenuation , 10);
	for (int i = 0 ; i < 10 ; ++i)
	{
		attenuation[i] = temp[i];
	}
}
void EEProm::setAttenuation(char *attenuation)
{
	eeprom_update_block (( const void *) attenuation , (void *)NonVolatileAttenuation, 10);
}
void EEProm::getPower(char power[])
{
	uint8_t temp[10];
	eeprom_read_block (( void *) temp , ( const void *) NonVolatilePower , 10);
	for (int i = 0 ; i < 10 ; ++i)
	{
		power[i] = temp[i];
	}
}
void EEProm::setPower(char *power)
{
	eeprom_update_block (( const void *) power , (void *)NonVolatilePower, 10);
}
void EEProm::getId(char id[])
{
	uint8_t temp[10];
	eeprom_read_block (( void *) temp , ( const void *) NonvolatileId , 10);
	for (int i = 0 ; i < 10 ; ++i)
	{
		id[i] = temp[i];
	}
}
void EEProm::setId(char *id)
{
	eeprom_update_block (( const void *) id , (void *)NonvolatileId, 10);
}
