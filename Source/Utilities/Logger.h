#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>

namespace DronsEngine {
	class Logger
	{
	private:
		bool isOpened;
		std::ofstream logStream;
		std::string path;
		
	public:
		Logger();
		Logger(std::string path);
		~Logger();
		void open(std::string path);
		void close();
		bool isOpen();
		void log(std::string message);
		void logWarning(std::string message);
		void logError(std::string message);
	};
}  // namespace DronsEngine
