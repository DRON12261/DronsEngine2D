#include "GameLogger.h"

DronsEngine::GameLogger& DronsEngine::GameLogger::get()
{
	static GameLogger instance;
	return instance;
}

void DronsEngine::GameLogger::log(std::string message)
{
	get().logger.log(message);
}

void DronsEngine::GameLogger::logWarning(std::string message)
{
	get().logger.logWarning(message);
}

void DronsEngine::GameLogger::logError(std::string message)
{
	get().logger.logError(message);
}

DronsEngine::GameLogger::GameLogger()
{
	if (!logger.isOpen())
	{
		auto t = std::time(nullptr);
		std::tm tm{};
		localtime_s(&tm, &t);

		std::ostringstream oss;
		oss << std::put_time(&tm, "[%d.%m.%Y]");
		auto dateStr = oss.str();

		logger.open("Logs/log" + dateStr + ".txt");
	}
}