#include <avr/io.h>
#include "Receiver.h"
#include <string.h>

Receiver::Receiver() {
	
}
void Receiver::setLastUpdatedTime(char *epoch) {
	memcpy(this->lastUpdatedTime, &epoch[0], 15);
}
void Receiver::setAttenuation(char *atten) {
	memcpy(this->attenuation, &atten[0], 5);
}
void Receiver::setMacAddress(char *mac) {
	memcpy(this->macAddress, &mac[0], 30);
}
