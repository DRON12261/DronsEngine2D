#pragma once

#include <string>
#include <iomanip>
#include <ctime>
#include <sstream>

#include "Logger.h"

namespace DronsEngine {
	class GameLogger
	{
	private:
		Logger m_logger;
		GameLogger();

	public:
		static GameLogger& get();
		static void log(std::string t_message, Logger::Type t_type = Logger::Type::LOG_INFO, std::string t_scope = "");

		GameLogger(const GameLogger&) = delete;
		void operator=(const GameLogger&) = delete;
	};
}  // namespace DronsEngine
