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
		DronsEngine::Logger m_logger;
		GameLogger();

	public:
		static GameLogger& get();
		static void log(std::string t_message);
		static void logWarning(std::string t_message);
		static void logError(std::string t_message);

		GameLogger(const GameLogger&) = delete;
		void operator=(const GameLogger&) = delete;
	};
}  // namespace DronsEngine
