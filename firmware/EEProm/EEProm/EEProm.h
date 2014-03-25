class EEProm
{
	private:
	public:
		EEProm();
		void getBaud(char baud[]);
		void getAttenuation(char attenuation[]);
		void getPower(char power[]);
		void getId(char id[]);
		
		void setId(char *id);
		void setPower(char *power);
		void setAttenuation(char *attenuation);
		void setBaud(char *baud);
};