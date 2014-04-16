#include <avr/io.h>
#include "Receiver.h"
#include <string.h>

Receiver::Receiver() {
	
}
void Receiver::setLastUpdatedTime(char epoch[]) {
	memcpy(this->lastUpdatedTime, &epoch[0], 15);
}
void Receiver::setAttenuation(char atten[]) {
	memcpy(this->attenuation, &atten[0], 5);
}
void Receiver::setMacAddress(char mac[]) {
	memcpy(this->macAddress, &mac[0], 10);
}

void Receiver::toString(char string[]) {
	strcat(string, "MAC=");
	strcat(string, this->macAddress);
	strcat(string, "&ATTEN=");
	strcat(string, this->attenuation);
	strcat(string, "&TIME=");
	strcat(string, this->lastUpdatedTime);
}
void Receiver::clear() {
	uint16_t lastUpdatedTimeLength = 0;
	uint16_t attenuationLength = 0;
	uint16_t macAddressLength = 0;
	while(this->lastUpdatedTime[lastUpdatedTimeLength] != 0) {
		lastUpdatedTimeLength++;
	}
	while(this->attenuation[attenuationLength] != 0) {
		attenuationLength++;
	}
	while(this->macAddress[macAddressLength] != 0) {
		macAddressLength++;
	}
	memset(this->lastUpdatedTime, 0, lastUpdatedTimeLength);
	memset(this->attenuation, 0, attenuationLength);
	memset(this->macAddress, 0, macAddressLength);
}
