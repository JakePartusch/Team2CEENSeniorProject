#include <avr/io.h>
#include <string.h>
#include "Multiplexer.h"
#include "USART.h"
#define F_CPU 16000000UL
#include <avr/delay.h>
#include <stdio.h>

#define S0 3
#define S1 4
#define NUMBER_OF_RECEIVERS 3

USART usart1;
Multiplexer::Multiplexer() {
	
}

void Multiplexer::init(Receiver *receivers) {
	this->receivers = receivers;
	this->currentPort = 0;
	this->bufferIndex = 0;
	DDRB |= (1<< S0);
	DDRB |= (1<< S1);
}

void Multiplexer:: incrementPort() {
	switch (currentPort) {
		case 0:            // Note the colon, not a semicolon
			PORTB &= ~(1<< S0);
			PORTB |= (1<< S1);
			currentPort = 1;
		break;
		case 1:            // Note the colon, not a semicolon
			PORTB &= ~(1<< S1);
			PORTB |= (1<< S0);
			currentPort = 2;
		break;
		case 2:            // Note the colon, not a semicolon
			PORTB &= ~(1<< S0);
			PORTB &= ~(1<< S1);
			currentPort = 0;
		break;
	}
}

void Multiplexer:: addToBuffer(char c) 
{
	if(c == '\n') {
		fullBuffer = 1;		
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
void Multiplexer::parseBuffer() {
	if(verifyCorrectBeginning()) {
		uint16_t macStart = 4;
		uint16_t macEnd = getNextAmpersand(macStart);
		uint16_t macLength = macEnd - macStart;
		
		uint16_t attenuationStart = macEnd + 1;
		uint16_t attenuationEnd = getNextAmpersand(macEnd + 1);
		uint16_t attenuationLength = attenuationEnd -attenuationStart;
		
		uint16_t timeStart = attenuationEnd + 1;
		uint16_t timeEnd = bufferIndex;
		uint16_t timeLength = timeEnd - timeStart;
		if(macLength > 3 &&  attenuationLength > 2 && timeLength > 5) {
			memset((char *)receivers[currentPort].macAddress,	0, sizeof(receivers[currentPort].macAddress));
			memset((char *)receivers[currentPort].attenuation,	0, sizeof(receivers[currentPort].attenuation));
			memset((char *)receivers[currentPort].time,			0, sizeof(receivers[currentPort].time));
			
			memcpy((char *)receivers[currentPort].macAddress,  (char *)&buffer[macStart],         (macLength));
			memcpy((char *)receivers[currentPort].attenuation, (char *)&buffer[attenuationStart], (attenuationLength));
			memcpy((char *)receivers[currentPort].time,        (char *)&buffer[timeStart],        (timeLength));
		}
	}
	memset((char *)&buffer[0], 0, sizeof(buffer));
	bufferIndex = 0;
	fullBuffer = 0;
	
}

bool Multiplexer::verifyCorrectBeginning() {
	if(bufferIndex > 2) {
		if(buffer[0] == 'R' && buffer[1] == 'E' && buffer[2] == 'C' && buffer[3] == '=') {
			return true;
		}
	}
	return false;
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
		strcat(string, "NODE=1");
	for(int i = 0; i < NUMBER_OF_RECEIVERS; i++) {
		char intToString[16];
		snprintf(intToString, sizeof(intToString), "%d", i+1);
		strcat(string, "&PORT=");
		strcat(string, intToString);
		strcat(string, "&ATTEN=");
		strcat(string, (char *)receivers[i].attenuation);
	}
	strcat(string, "\n");
}

bool Multiplexer::isReceivingData() {
	if(bufferIndex != 0) {
		return true;
	}
	else {
		return false;
	}
}
void Multiplexer::clearAllReceivers() {
	for(int i = 0; i < NUMBER_OF_RECEIVERS; i++) {
		memset((char *)receivers[i].macAddress, 0, sizeof(receivers[i].macAddress));
		memset((char *)receivers[i].attenuation, 0, sizeof(receivers[i].attenuation));
		memset((char *)receivers[i].time, 0, sizeof(receivers[i].time));
	}
}
bool Multiplexer::isBufferFull() {
	if(fullBuffer == 1) {
		return true;
	}
	else {
		return false;
	}
}