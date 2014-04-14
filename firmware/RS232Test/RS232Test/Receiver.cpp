#include <avr/io.h>
#include "Receiver.h"
#include <string.h>

Receiver::Receiver() {
	
}
void Receiver::setLastUpdatedTime(char *epoch) {
	//memset(this->lastUpdatedTime, 0, 15);
	memcpy(this->lastUpdatedTime, &epoch[0], 15);
}
void Receiver::setAttenuation(char *atten) {
	//memset(this->attenuation, 0, 5);
	memcpy(this->attenuation, &atten[0], 5);
}
void Receiver::setMacAddress(char *mac) {
	//memset(this->macAddress, 0, 30);
	memcpy(this->macAddress, &mac[0], 30);
}

void Receiver::toString(char *string) {
	strcpy(string, "MAC=");
	strcat(string, this->macAddress);
	strcat(string, "&ATTEN=");
	strcat(string, this->attenuation);
	strcat(string, "&TIME=");
	strcat(string, this->lastUpdatedTime);
}
