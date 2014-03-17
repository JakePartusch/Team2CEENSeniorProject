/*
 * EEProm.cpp
 *
 * Created: 3/10/2014 12:07:41 PM
 *  Author: Jake
 */ 
#include <avr/io.h>
#include <avr/eeprom.h>
#include "EEProm.h"
uint16_t EEMEM NonVolatileAttenuation;
uint16_t EEMEM NonVolatileBaud;
uint16_t EEMEM NonVolatilePower;
uint16_t EEMEM NonvolatileId;

EEProm::EEProm()
{}

unsigned int EEProm::getBaud()
{
	return eeprom_read_word (&NonVolatileBaud);
}
void EEProm::setBaud(uint16_t baud)
{
	eeprom_update_word(&NonVolatileBaud, baud);
}
uint16_t EEProm::getAttenuation()
{
	return eeprom_read_word (&NonVolatileAttenuation);
}
void EEProm::setAttenuation(uint16_t attenuation)
{
	eeprom_update_word(&NonVolatileAttenuation, attenuation);
}
uint16_t EEProm::getPower()
{
	return eeprom_read_word (&NonVolatilePower);
}
void EEProm::setPower(uint16_t power)
{
	eeprom_update_word(&NonVolatilePower, power);
}
uint16_t EEProm::getId()
{
	return eeprom_read_word(&NonvolatileId);
}
void EEProm::setId(uint16_t id)
{
	eeprom_update_word(&NonvolatileId, id);
}
