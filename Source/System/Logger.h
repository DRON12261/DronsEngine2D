#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>

#include "ConsoleColor.h"

namespace DronsEngine {
	class Logger
	{
	private:
		bool m_isOpened;
		std::ofstream m_logStream;
		std::string m_path;
		
	public:
		Logger();
		Logger(std::string t_path);
		~Logger();
		void open(std::string t_path);
		void close();
		bool isOpen();
		void log(std::string t_message);
		void logWarning(std::string t_message);
		void logError(std::string t_message);
	};
}  // namespace DronsEngine
