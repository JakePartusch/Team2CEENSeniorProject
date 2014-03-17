class EEProm
{
	private:
	public:
		EEProm();
		uint16_t getBaud();
		uint16_t getAttenuation();
		uint16_t getPower();
		uint16_t getId();
		
		void setId(uint16_t id);
		void setPower(uint16_t power);
		void setAttenuation(uint16_t attenuation);
		void setBaud(uint16_t baud);
};