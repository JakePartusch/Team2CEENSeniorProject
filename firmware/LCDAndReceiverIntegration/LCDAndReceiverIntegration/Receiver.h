#ifndef RECEIVER_H
#define RECEIVER_H

#include "Receiver.h"
class Receiver {
	private:
		
	public:
		Receiver();
		volatile uint8_t attenuation[5];
		volatile uint8_t serialNumber[15];
	};
#endif