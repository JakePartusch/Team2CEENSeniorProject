#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "Multiplexer.h"
#include "USART.h"
#define F_CPU 16000000UL
#include <util/delay.h>
#define S0 3
#define S1 4

USART usart1 = USART(1,103);
long convertToInt(char array[]);
Multiplexer::Multiplexer()
{
	this->currentPort = 0;
	this->bufferIndex = 0;
	DDRB |= (1<< S0);
	DDRB |= (1<< S1);
	UCSR1B |= (1 << RXCIE1 );
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
	uint16_t currentPort = currentPort; //port could change while in this method
	cli();
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
	usart1.transmit_Str(receivers[currentPort].macAddress);
	_delay_ms(10);
	usart1.transmit_Str(receivers[currentPort].attenuation);
	_delay_ms(10);
	usart1.transmit_Str(receivers[currentPort].lastUpdatedTime);
	_delay_ms(10);
	sei();
}

void Multiplexer::parseBuffer(uint16_t port) {
	//REC=0x001369&-102&1397187777
	if(verifyCorrectBeginning()) {
		uint16_t macEndIndex = getNextAmpersand(4);
		if(macEndIndex != 0) {
			uint16_t attenuationStartIndex = macEndIndex + 1;
			uint16_t attenuationEndIndex = getNextAmpersand(attenuationStartIndex);
			if(attenuationEndIndex != 0) {
				uint16_t timeStartIndex = attenuationEndIndex + 1;

				char macAddress[30];
				char attenuation[5];
				char time[15];
				memcpy(macAddress, &buffer[4], macEndIndex - 4);
				memcpy(attenuation, &buffer[attenuationStartIndex], attenuationEndIndex - (attenuationStartIndex));
				memcpy(time, &buffer[timeStartIndex], bufferIndex - (timeStartIndex));
				
				int timeLength = 0;
				while(time[timeLength] != 0) {
					timeLength++;
				}
				if(timeLength > 9) {
					receivers[port].setMacAddress(macAddress);
					receivers[port].setAttenuation(attenuation);
					receivers[port].setLastUpdatedTime(time);
				}
				memset(&macAddress[0], 0, sizeof(macAddress));
				memset(&attenuation[0], 0, sizeof(attenuation));
				memset(&time[0], 0, sizeof(time));
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

uint16_t Multiplexer::getNextAmpersand(uint16_t index) {
	for (int i = index; i < bufferIndex; i++) {
		if(buffer[i] == '&') {
			return i;
		}
	}
	return 0;
}