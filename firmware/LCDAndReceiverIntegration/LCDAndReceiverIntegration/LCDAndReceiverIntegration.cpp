#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

#include "Receiver.h"
#include "USART.h"
#include "Timer.h"
#include "Multiplexer.h"
#include "lcd.h"

#define NUMBER_OF_RECEIVERS 3

USART usart;
Multiplexer multiplexer;
Timer xbeeTimer;
Timer muxTimer;
LCD lcd;

Receiver receivers[NUMBER_OF_RECEIVERS];
volatile uint8_t receiverData[200];
volatile uint8_t isSendXbeeTime = 0;
volatile uint8_t byteReceived;
volatile uint8_t isLcdSelect = 0;
void enableInterrupts();

int main(void)
{
	for(int i = 0; i < NUMBER_OF_RECEIVERS; i++) {
		receivers[i] = Receiver();
		memset((char *)receivers[i].attenuation, 0, 5);
	}
	
	lcd = LCD(receivers);
	multiplexer.init(receivers);
	usart.init(103);
	xbeeTimer.init(1, 49910);
	muxTimer.init(3, 49910);
	multiplexer.clearAllReceivers();
	enableInterrupts();
	uint16_t refreshCount = 0;
	sei();
	while(1) {
		if(multiplexer.isBufferFull()) {
			cli();
			multiplexer.parseBuffer();
			sei();
		}
		if(isSendXbeeTime == 1) {
			cli();
			if(refreshCount == 4){
				lcd.refresh();
				refreshCount = 0;
			}
			else {
				refreshCount++;
			}
			memset((char *) receiverData, 0, sizeof(receiverData));
			multiplexer.getReceiversString((char *)receiverData);
			usart.transmit_Str((char *)receiverData);
			isSendXbeeTime = 0;
			sei();
		}
		if(isLcdSelect == 1) {
			cli();
			lcd.select();
			isLcdSelect = 0;
			sei();
		}
	}
}

void enableInterrupts()
{
	PCMSK0 |= (1<<PCINT5);
	PCMSK0 |= (1<<PCINT6);
	PCMSK0 |= (1<<PCINT7);
	PCICR |= (1<< PCIE0);
}

ISR(PCINT0_vect) {
	if(!(PINA & (1<<PINA5)))
	{
		lcd.moveSelectedDown();
	}
	if(!(PINA & (1<<PINA6)))
	{
		isLcdSelect = 1;
	}
	if(!(PINA & (1<<PINA7)))
	{
		lcd.moveSelectedUp();
	}
	_delay_ms(100);
}
ISR (USART1_RX_vect) {
	byteReceived = UDR1;
	multiplexer.addToBuffer(byteReceived);
}
ISR (TIMER1_OVF_vect) {
	isSendXbeeTime = 1;
	xbeeTimer.reset();
}
ISR (TIMER3_OVF_vect) {
	if(!multiplexer.isReceivingData()) {
		multiplexer.incrementPort();
	}
	muxTimer.reset();
}
ISR(WDT_vect) {
	memset((char *)receiverData, 0, sizeof(receiverData));
}
