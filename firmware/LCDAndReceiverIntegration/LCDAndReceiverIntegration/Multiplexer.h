#include "Receiver.h"
class Multiplexer {
	private:
		int fullBuffer;
		uint16_t currentPort;
		volatile uint8_t buffer[50];
		int bufferIndex;
		bool verifyCorrectBeginning();
		uint16_t getNextAmpersand(uint16_t index);
				
	public:
		Multiplexer();
		bool isReceivingData();
		void init(Receiver *receivers);
		void incrementPort();
		void addToBuffer(char c);
		void getReceiversString(char *string);
		void clearAllReceivers();
		bool isBufferFull();
		void parseBuffer();
		Receiver *receivers;
	};