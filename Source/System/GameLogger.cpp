#include "GameLogger.h"

DronsEngine::GameLogger& DronsEngine::GameLogger::get()
{
	static GameLogger instance;
	return instance;
}

void DronsEngine::GameLogger::log(std::string t_message, Logger::Type t_type, std::string t_scope)
{
	get().m_logger.log(t_message, t_type, t_scope);
}

DronsEngine::GameLogger::GameLogger()
{
	if (!m_logger.isOpen())
	{
		//rewrite varnames
		auto t = std::time(nullptr);
		std::tm tm{};
		localtime_s(&tm, &t);

		std::ostringstream oss;
		oss << std::put_time(&tm, "[%d.%m.%Y]");
		auto dateStr = oss.str();

		m_logger.open("Logs/log" + dateStr + ".log");
	}
}