class LCD
{
	private:
		Field receiverFields[4];
		Field transmitterFields[4];
		Field menuFields[4];
		Field homeFields[3];
	public:
		Screen buildTransmitterScreen();
		Screen buildReceiverScreen();
		Screen buildHomeScreen();
		Screen buildMenuScreen();
		LCD();
};