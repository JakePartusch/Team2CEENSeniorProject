#include <avr/io.h>
#include "Timer.h"

Timer::Timer() {
}

void Timer::init(uint16_t id, uint16_t length) {
	this->id = id;
	this->length = length;
	switch (id) {
		case 1:
			TIMSK1 |= (1 << TOIE1 ); // Enable overflow interrupt
			TCNT1 = this->length; // Preload timer with precalculated value
			TCCR1B |= ((1 << CS02) | (1<<CS00));
			break;
		case 3:
			TIMSK3 |= (1 << TOIE3);
			TCNT3 = this->length;
			TCCR3B |= ((1 << CS02));
			break;
	}
}

void Timer::reset() {
	switch(id) {
		case 1:
			TCNT1 = length;
			break;
		case 3:
			TCNT3 = length;
			break;
	}
}