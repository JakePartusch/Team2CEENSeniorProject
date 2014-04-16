class Receiver {
	private:
		
	public:
		Receiver();
		volatile uint8_t attenuation[5];
		volatile uint8_t macAddress[15];
		volatile uint8_t time[15];
	};