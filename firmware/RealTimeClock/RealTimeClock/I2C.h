class I2C
{
	public:
	I2C();
	void start(void);
	void stop(void);
	void write(uint8_t u8data);
	uint8_t readACK(void);
	uint8_t readNACK(void);
	uint8_t getStatus(void);
};