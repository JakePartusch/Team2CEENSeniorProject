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

int main(void) {
	
	usart.init(103);
	multiplexer.init();
	xbeeTimer.init(1, 49910);
	muxTimer.init(3, 49910);
	watchdog.init();	
		
	sei ();
    while(1) {
	}
}

ISR (USART1_RX_vect) {
	cli();
	char receivedByte = UDR1; 
	multiplexer.addToBuffer(receivedByte);
	sei();
}
ISR (TIMER1_OVF_vect) {
	cli();
	memset((char *) receiverData, 0, sizeof(receiverData));
	multiplexer.getReceiversString((char *)receiverData);
	usart.transmit_Str((char *)receiverData);
	xbeeTimer.reset();
	sei();
}
ISR (TIMER3_OVF_vect) {
	cli();
	if(!multiplexer.isReceivingData()) {
		multiplexer.incrementPort();
	}
	watchdog.reset();
	muxTimer.reset();
	sei();
}
ISR(WDT_vect) {
	memset((char *)receiverData, 0, sizeof(receiverData));
}