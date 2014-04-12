#include "Receiver.h"
class Multiplexer {
	private:
		uint16_t currentPort;
		char buffer[50];
		uint16_t bufferIndex;
		void parseBuffer(uint16_t port);
		int verifyCorrectBeginning();
		uint16_t getNextAmpersand(uint16_t index);
		void saveContents(uint16_t port, char macAddress[], char  attenuation[], char time[]);
	public:
		Multiplexer();
		void incrementPort();
		void addToBuffer(char c);
		Receiver receivers[];
	};