/*
 * RealTimeClock.cpp
 *
 * Created: 3/9/2014 10:38:23 PM
 *  Author: Jake
 */ 

#include <avr/io.h>
#include "I2C.h"

int function(void)
{
    I2C i2c = I2C();
	i2c.write('J');
}