class USART
{
	public:
		uint16_t port;
		USART(uint16_t port, uint16_t baud);
		void transmit( unsigned char data );
		void transmit_Str(char *data);
		void transmit_Int(uint16_t data);
		unsigned char receive();
		char* receive_Str();
};