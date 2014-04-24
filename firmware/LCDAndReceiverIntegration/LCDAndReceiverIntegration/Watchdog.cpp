#include <avr/io.h>
#include <avr/wdt.h>
#include "Watchdog.h"

Watchdog::Watchdog() {
}

void Watchdog::init() {
	//reset watchdog
	wdt_reset();
	//set up WDT interrupt
	WDTCSR = (1<<WDCE)|(1<<WDE);
	//Start watchdog timer with 4s prescaller
	WDTCSR = (1<<WDIE)|(1<<WDE)|(1<<WDP2) |(1<<WDP1)|(WDP0);
}

void Watchdog::reset() {
	wdt_reset();
}