class Receiver {
	private:
		char attenuation[5];
		char lastUpdatedTime[15];
		char macAddress[10];
	public:
		void setLastUpdatedTime(char epochTime[]);
		void setAttenuation(char attenuation[]);
		void setMacAddress(char macAddress[]);
		Receiver();
		void toString(char string[]);
		void clear();
	};