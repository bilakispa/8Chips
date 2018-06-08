//A simple logger class copied from DrDobb's code
#ifndef LOGGER_H
#define LOGGER_H
#include <sstream>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <chrono>

#include "clock.h"

namespace Chips {
	enum LogLevel {
		logERROR, logWARNING, logINFO, logDEBUG
	};
	
	class Logger {
	private:
		Logger() {}
		static std::chrono::steady_clock::time_point _startPoint;
	
	public:
		//C++11 Thread safe Singleton aproach
		static Logger& GetInstance() {
			static Logger instance;
			return instance;
		}
	
		//Remove copy constructors
		Logger(const Logger&) = delete;
		void operator = (Logger const &) = delete;
		
		static void Write(const std::string &);
		//Add << overloading (can it print too?)
	/*
		Log();
		virtual ~Log();
		std::ostringstream& Get(LogLevel level = logINFO);
	public:
		static LogLevel& ReportLevel();
		static std::string ToString(LogLevel level);
	protected:
		std::ostringstream oss;
	private:
		//remove copy constructors
		
	private:
		LogLevel msgLevel;
		Clock _clock;
		static int l;
		*/
	};
	
	inline void Write(const std::string & msg) {
		std::cout << msg << std::endl;
	}
	
	/*
	inline Log::Log() {
		//void
		l= 2;
	}
	
	inline LogLevel& Log::ReportLevel() {
		static LogLevel reportingLevel = logINFO;
   return reportingLevel;
	}
	
	inline std::ostringstream& Log::Get(LogLevel level) {
			oss << " - " << std::setprecision(5) << std::fixed << _clock.CountFromStart() << "s";
			oss << " [" << ToString(level) << "] ";
			msgLevel = level;
			return oss;
	}
	 
	inline Log::~Log() {
		if(msgLevel <= Log::ReportLevel()) {
			oss << std::endl;
			//fprintf(stderr, "%s", oss.str().c_str());
		//	fflush(stderr);
		}
	}
	
	inline std::string Log::ToString(LogLevel level) {
		static const char* const buffer[] = {
			"ERROR", "WARNING", "INFO", "DEBUG"
		};
		return buffer[level];
	}*/
}
#endif