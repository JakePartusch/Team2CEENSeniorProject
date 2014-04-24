#include "Receiver.h"
class Multiplexer {
	private:
		uint16_t currentPort;
		volatile uint8_t buffer[50];
		uint16_t bufferIndex;
		void parseBuffer();
		bool verifyCorrectBeginning();
		uint16_t getNextAmpersand(uint16_t index);
		Receiver receivers[];
	public:
		Multiplexer();
		bool isReceivingData();
		void init();
		void incrementPort();
		void addToBuffer(char c);
		void getReceiversString(char *string);
	};