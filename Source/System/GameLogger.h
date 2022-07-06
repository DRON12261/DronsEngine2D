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
		DronsEngine::Logger logger;
		GameLogger();

	public:
		static GameLogger& get();
		static void log(std::string message);
		static void logWarning(std::string message);
		static void logError(std::string message);

		GameLogger(const GameLogger&) = delete;
		void operator=(const GameLogger&) = delete;
	};
}  // namespace DronsEngine
