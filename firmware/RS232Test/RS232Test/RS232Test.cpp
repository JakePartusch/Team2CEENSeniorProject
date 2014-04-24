#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "Multiplexer.h"
#include "USART.h"
#include "Timer.h"
#include "Watchdog.h"


USART usart;
Multiplexer multiplexer;
Timer xbeeTimer;
Timer muxTimer;
Watchdog watchdog;

volatile uint8_t receiverData[200];
volatile uint8_t isSendXbeeTime = 0;
volatile uint8_t isUartReceive = 0;
volatile uint8_t byteReceived;

int main(void) {
	
	usart.init(103);
	multiplexer.init();
	xbeeTimer.init(1, 49910);
	muxTimer.init(3, 49910);
	watchdog.init();	
	multiplexer.clearAllReceivers();
		
	sei ();
    while(1) {
		if(isUartReceive == 1) {
			cli();
			multiplexer.addToBuffer(byteReceived);
			sei();
		}
		if(multiplexer.isBufferFull()) {
			cli();
			multiplexer.parseBuffer();
			sei();
		}
		if(isSendXbeeTime == 1) {
			cli();
			memset((char *) receiverData, 0, sizeof(receiverData));
			multiplexer.getReceiversString((char *)receiverData);
			usart.transmit_Str((char *)receiverData);
			isSendXbeeTime = 0;
			sei();
		}
	}
}

ISR (USART1_RX_vect) {
	byteReceived = UDR1; 
	isUartReceive = 1;
}
ISR (TIMER1_OVF_vect) {
	isSendXbeeTime = 1;
	xbeeTimer.reset();
	watchdog.reset();
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