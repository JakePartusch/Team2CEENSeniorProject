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
		int validateMacAddress(char macAddress[]);
		int validateAttenuation(char attenuation[]);
		int validateTime(char time[]);
		Receiver receivers[];
	public:
		Multiplexer();
		void incrementPort();
		void addToBuffer(char c);
		void getReceiversString(char *string);
	};