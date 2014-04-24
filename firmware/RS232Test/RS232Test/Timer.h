class Timer {
	private:
		uint16_t id;
		uint16_t length;
	public:
		Timer();
		void init(uint16_t id, uint16_t length);
		void reset();
	};