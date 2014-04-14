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

USART usart0 = USART(1,103);
long convertToInt(char array[]);

Multiplexer::Multiplexer()
{
	this->currentPort = 0;
	this->bufferIndex = 0;
	DDRB |= (1<< S0);
	DDRB |= (1<< S1);
	this->receivers[0] = Receiver();
	this->receivers[1] = Receiver();
	this->receivers[2] = Receiver();
	//make sure to enable global interrupts
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
	uint16_t currentPort = this->currentPort; //port could change while in this method
	cli();
	if(c != '\r') {
		if(c == '\n') {
			parseBuffer(currentPort);
			memset(&buffer[0], 0, sizeof(buffer));
			bufferIndex = 0;
		}
		else if(bufferIndex == 50) {
			memset(&buffer[0], 0, sizeof(buffer));
			bufferIndex = 0;
		}
		else {
			buffer[bufferIndex] = c;
			bufferIndex++;
		}
	}
	sei();
}

void Multiplexer::parseBuffer(uint16_t port) {
	//REC=0x001369&-102&1397187777
	usart0.transmit_Str(this->buffer);
	if(verifyCorrectBeginning()) {
		uint16_t macEndIndex = getNextAmpersand(4);
		if(macEndIndex != 0) {
			uint16_t attenuationStartIndex = macEndIndex + 1;
			uint16_t attenuationEndIndex = getNextAmpersand(attenuationStartIndex);
			if(attenuationEndIndex != 0) {
				uint16_t timeStartIndex = attenuationEndIndex + 1;

				char* macAddress = (char*) malloc(30); 
				char* attenuation = (char*) malloc(5);
				char* time = (char*) malloc(15);
					
				memcpy(macAddress, &buffer[4], macEndIndex - 4);
				memcpy(attenuation, &buffer[attenuationStartIndex], attenuationEndIndex - (attenuationStartIndex));
				memcpy(time, &buffer[timeStartIndex], bufferIndex - (timeStartIndex));
				if(validateMacAddress(macAddress) && validateAttenuation(attenuation) && validateTime(time))
				{
					receivers[port].setMacAddress(macAddress);
					receivers[port].setAttenuation(attenuation);
					receivers[port].setLastUpdatedTime(time);
				}
				free(macAddress);
				free(attenuation);
				free(time);
			}
		}
	}
}
void Multiplexer::saveContents(uint16_t port, char macAddress[], char attenuation[], char time[]) {
	receivers[port].setMacAddress(macAddress);
	receivers[port].setAttenuation(attenuation);
	receivers[port].setLastUpdatedTime(time);
}

int Multiplexer::verifyCorrectBeginning() {
	if(bufferIndex > 2) {
		if(buffer[0]== 'R' && buffer[1] == 'E' && buffer[2] == 'C' && buffer[3] == '=') {
			return 1;
		}
	}
	return 0;
}

int Multiplexer::validateMacAddress(char macAddress[]) {
	usart0.transmit_Str("Mac");
	_delay_ms(10);
	if(macAddress[0] != '0' || macAddress[1] != 'x') {
		return 0;
	}
	int i = 2;
	while(macAddress[i] != 0) {
		if(!isxdigit(macAddress[i])) {
			return 0;
		}
		if(i == 10) {
			return 0;
		}
		i++;
	}
	return 1;
}
int Multiplexer::validateAttenuation(char attenuation[]) {
	usart0.transmit_Str("Atten");
	_delay_ms(10);
	if(attenuation[0] != '-') {
		return 0;
	}
	int i = 1;
	while(attenuation[i] != 0) {
		if(!isdigit(attenuation[i])) {
			return 0;
		}
		if(i == 5) {
			return 0;
		}
		i++;
	}
	return 1;
}
int Multiplexer::validateTime(char time[]) {
	usart0.transmit_Str("Time");
	_delay_ms(10);
	int timeLength = 0;
	while(time[timeLength] != 0) {
		if(!isdigit(time[timeLength])) {
			return 0;
		}
		timeLength++;
	}
	if(timeLength != 10) {
		return 0;
	}
	return 1;
}

uint16_t Multiplexer::getNextAmpersand(uint16_t index) {
	for (int i = index; i < bufferIndex; i++) {
		if(buffer[i] == '&') {
			return i;
		}
	}
	return 0;
}

void Multiplexer::getReceiversString(char * string) {
	char receiver0string[80];
	receivers[0].toString(receiver0string);
	char receiver1string[80];
	receivers[1].toString(receiver1string);
	char receiver2string[80];
	receivers[2].toString(receiver2string);
	strcpy(string, receiver0string);
	strcat(string, receiver1string);
	strcat(string, receiver2string);
}