#include "Receiver.h"
class Multiplexer {
	private:
		uint16_t currentPort;
		volatile uint8_t buffer[50];
		uint16_t bufferIndex;
		void parseBuffer(uint16_t port);
		bool verifyCorrectBeginning();
		uint16_t getNextAmpersand(uint16_t index);
		void saveContents(uint16_t port, char macAddress[], char  attenuation[], char time[]);
		bool validateMacAddress(char macAddress[]);
		bool validateAttenuation(char attenuation[]);
		bool validateTime(char time[]);
		Receiver receivers[];
	public:
		Multiplexer();
		bool isReceivingData();
		void init();
		void incrementPort();
		void addToBuffer(char c);
		void getReceiversString(char *string);
		void clearAllReceivers();
	};