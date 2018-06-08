#ifndef CLOCK_H
#define CLOCK_H
#include <chrono>

namespace Chips {
	class Clock {
	private:
		std::chrono::steady_clock::time_point _prevTime, _nowTime;
		
	public:
		Clock();
		
		static std::chrono::steady_clock::time_point& StartTime();
		static double CountFromStart();
		void CountFromPrev();
	};
	
	inline Clock::Clock() {

	}
	
	inline std::chrono::steady_clock::time_point& Clock::StartTime() {
		static std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
		return start;
	}
	
	inline double Clock::CountFromStart() {
		std::chrono::duration<double> dur(std::chrono::steady_clock::now() - StartTime());
		return dur.count();
	}
}
#endif