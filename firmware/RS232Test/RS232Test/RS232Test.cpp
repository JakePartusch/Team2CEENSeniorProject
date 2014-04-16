#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/wdt.h>
#include <string.h>
#include "Multiplexer.h"
#include "USART.h"

USART usart;
Multiplexer multiplexer;
volatile uint8_t receiverData[200];
int main(void) {
	
	usart.init(103);
	multiplexer.init();
	
	//reset watchdog
	wdt_reset();
	//set up WDT interrupt
	WDTCSR = (1<<WDCE)|(1<<WDE);
	//Start watchdog timer with 4s prescaller
	WDTCSR = (1<<WDIE)|(1<<WDE)|(1<<WDP3);
	
	TIMSK1 |= (1 << TOIE1 ); // Enable overflow interrupt
	TCNT1 = 49910; // Preload timer with precalculated value
	TCCR1B |= ((1 << CS02) | (1<<CS00));
	
	TIMSK3 |= (1 << TOIE3);
	TCNT3 = 49910;
	TCCR3B |= ((1 << CS02));	
	
	sei ();
    while(1) {
	}
}

ISR (USART1_RX_vect) {
	cli();
	char receivedByte ;
	receivedByte = UDR1; // Fetch the received byte value into the variable " ByteReceived "
	//usart.transmit(receivedByte);
	multiplexer.addToBuffer(receivedByte);
	sei();
}
ISR (TIMER1_OVF_vect) {
	cli();
	memset((char *) receiverData, 0, sizeof(receiverData));
	multiplexer.getReceiversString((char *)receiverData);
	usart.transmit_Str((char *)receiverData);
	TCNT1 = 49910;
	sei();
}
ISR (TIMER3_OVF_vect) {
	cli();
	wdt_reset();
	if(!multiplexer.isReceivingData()) {
		multiplexer.incrementPort();
	}
	TCNT1 = 52000;
	sei();
}
ISR(WDT_vect) {
	memset((char *)receiverData, 0, sizeof(receiverData));
	multiplexer.clearAllReceivers();
}