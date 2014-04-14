class Receiver {
	private:
		
		
	public:
		char attenuation[5];
		char lastUpdatedTime[15];
		char macAddress[30];
		void setLastUpdatedTime(char *epochTime);
		void setAttenuation(char *attenuation);
		void setMacAddress(char *macAddress);
		Receiver();
		void toString(char *string);
	};