class USART
{
	public:
		USART();
		void init(uint16_t baud);
		void transmit( unsigned char data );
		void transmit_Str(char *data);
};