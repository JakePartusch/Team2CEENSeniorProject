#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <ctype.h>
#include "Multiplexer.h"
#include "USART.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdlib.h>
#define S0 3
#define S1 4

USART usart1;

volatile uint8_t attenuation[5];
volatile uint8_t macAddress[15];
volatile uint8_t time[15];

Multiplexer::Multiplexer() {
}

void Multiplexer::init() {
	this->currentPort = 0;
	this->bufferIndex = 0;
	DDRB |= (1<< S0);
	DDRB |= (1<< S1);
	this->receivers[0] = Receiver();
	this->receivers[1] = Receiver();
	this->receivers[2] = Receiver();
}

void Multiplexer:: incrementPort() {
	switch (this->currentPort) {
		case 0:            // Note the colon, not a semicolon
			PORTB &= ~(1<< S0);
			PORTB |= (1<< S1);
			this->currentPort = 1;
		break;
		case 1:            // Note the colon, not a semicolon
			PORTB &= ~(1<< S1);
			PORTB |= (1<< S0);
			this->currentPort = 2;
		break;
		case 2:            // Note the colon, not a semicolon
			PORTB &= ~(1<< S0);
			PORTB &= ~(1<< S1);
			this->currentPort = 0;
		break;
	}
}

void Multiplexer:: addToBuffer(char c) 
{
	//REC=0x000131F&-101&13787777\n
	uint16_t currentPort = this->currentPort; //port could change while in this method
	if(c == '\n') {
		parseBuffer(currentPort);
		memset((char *)&buffer[0], 0, sizeof(buffer));
		bufferIndex = 0;
	}
	else if(bufferIndex == 50) {
		memset((char *)&buffer[0], 0, sizeof(buffer));
		bufferIndex = 0;
	}
	else {
		buffer[bufferIndex] = c;
		bufferIndex++;
	}
}
//REC=0x000131F&-101&13787777\n
void Multiplexer::parseBuffer(uint16_t port) {
	if(verifyCorrectBeginning()) {
		uint16_t macStart = 4;
		uint16_t macEnd = getNextAmpersand(macStart);
		uint16_t attenuationStart = macEnd + 1;
		uint16_t attenuationEnd = getNextAmpersand(macEnd + 1);
		uint16_t timeStart = attenuationEnd + 1;
		uint16_t timeEnd = bufferIndex;
		if(macEnd != 0 &&  attenuationEnd != 0) {
			
			//char* macAddress = (char*) malloc(10);
			//char* time = (char*) malloc(15);
					
			memcpy((char *)macAddress, (char *)&buffer[macStart], (macEnd - macStart));
			memcpy((char *)attenuation, (char *)&buffer[attenuationStart], (attenuationEnd - attenuationStart));
			memcpy((char *)time, (char *)&buffer[timeStart], (bufferIndex - timeStart));
			
			//Rethink validation.. could be breaking here
			//if(validateMacAddress(macAddress) && validateAttenuation(attenuation) && validateTime(time))
			//{
				usart1.transmit_Str("WRITING!");
				_delay_ms(10);
				//receivers[port].clear();
				//receivers[port].setMacAddress(macAddress);
				//receivers[port].setAttenuation(attenuation);
				//receivers[port].setLastUpdatedTime(time);
			//}
			
			//free(macAddress);
			//free(attenuation);
			//free(time);
		}
	}
}

bool Multiplexer::verifyCorrectBeginning() {
	if(bufferIndex > 2) {
		if(buffer[0] == 'R' && buffer[1] == 'E' && buffer[2] == 'C' && buffer[3] == '=') {
			return true;
		}
	}
	return false;
}

bool Multiplexer::validateMacAddress(char macAddress[]) {
	if(macAddress[0] != '0' && macAddress[1] != 'x') {
		return false;
	}
	int i = 2;
	while(macAddress[i] != 0) {
		if(!isxdigit(macAddress[i])) {
			return false;
		}
		if(i > 10) {
			return false;
		}
		i++;
	}
	return true;
}
bool Multiplexer::validateAttenuation(char attenuation[]) {
	if(attenuation[0] != '-') {
		return false;
	}
	int i = 1;
	while(attenuation[i] != 0) {
		if(!isdigit(attenuation[i])) {
			return false;
		}
		if(i > 5) {
			return false;
		}
		i++;
	}
	return true;
}
bool Multiplexer::validateTime(char time[]) {
	int timeLength = 0;
	while(time[timeLength] != 0) {
		if(!isdigit(time[timeLength])) {
			return false;
		}
		timeLength++;
	}
	if(timeLength != 10) {
		return false;
	}
	return true;
}

uint16_t Multiplexer::getNextAmpersand(uint16_t index) {
	for (int i = index; i < bufferIndex; i++) {
		if(buffer[i] == '&') {
			return i;
		}
	}
	return 0;
}

void Multiplexer::getReceiversString(char *string) {
	//receivers[0].toString(string);
	//receivers[1].toString(string);
	//receivers[2].toString(string);
	strcat(string, "MAC=");
	strcat(string, (char *)macAddress);
	strcat(string, "&ATTEN=");
	strcat(string, (char *)attenuation);
	strcat(string, "&TIME=");
	strcat(string, (char *)time);
}

void Multiplexer::clearAllReceivers() {
	receivers[0].clear();
	receivers[1].clear();
	receivers[2].clear();
}

bool Multiplexer::isReceivingData() {
	if(this->bufferIndex != 0) {
		return true;
	}
	else {
		return false;
	}
}