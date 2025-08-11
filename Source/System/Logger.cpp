#include "Logger.h"

DronsEngine::Logger::Logger(std::string t_path)
{
	m_isOpened = false;
	t_path = "";
	open(t_path);
}

DronsEngine::Logger::Logger()
{
	m_isOpened = false;
	m_path = "";
}

DronsEngine::Logger::~Logger()
{
	close();
}

void DronsEngine::Logger::open(std::string t_path)
{
	m_logStream.open(t_path, std::ofstream::out | std::ofstream::app);

	if (!m_logStream.is_open())
	{
		std::cerr << "Failed to open log file \"" << t_path << "\"." << std::endl;
		exit(1);
	}

	m_isOpened = true;
	this->m_path = t_path;
}

void DronsEngine::Logger::close()
{
	if (m_logStream.is_open())
	{
		m_logStream << std::endl << std::endl << std::endl;
		m_logStream.close();
	}

	m_isOpened = false;
	m_path = "";
}

bool DronsEngine::Logger::isOpen() const
{
	return m_isOpened;
}

void DronsEngine::Logger::log(std::string t_message, Type t_type, std::string t_scope)
{
#ifndef _DEBUG
	if (t_type == Type::LOG_DEBUG)
		return;
#endif

	if (t_message.empty())
		return;

	if (t_scope.empty())
		t_scope = "UNDEFINED";

	auto t = std::time(nullptr);
	std::tm tm{};
	localtime_s(&tm, &t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "[%d.%m.%Y | %H:%M:%S]");
	auto dateStr = oss.str();

	std::string loggerConPrefix = "";
	std::string loggerPrefix = "";
	switch (t_type)
	{
		case Type::LOG_INFO:
			loggerPrefix = "[INFO ]";
			loggerConPrefix = ConsoleColor::fg_black + ConsoleColor::bg_light_green + loggerPrefix + ConsoleColor::bg_black +
			                  ConsoleColor::fg_light_green;
			break;
		case Type::LOG_DEBUG:
			loggerPrefix = "[DEBUG]";
			loggerConPrefix = ConsoleColor::fg_black + ConsoleColor::bg_light_blue + loggerPrefix + ConsoleColor::bg_black +
			                  ConsoleColor::fg_light_blue;
			break;
		case Type::LOG_WARNING:
			loggerPrefix = "[WARN ]";
			loggerConPrefix = ConsoleColor::fg_black + ConsoleColor::bg_yellow + loggerPrefix + ConsoleColor::bg_black +
			                  ConsoleColor::fg_light_yellow;
			break;
		case Type::LOG_ERROR:
			loggerPrefix = "[ERROR]";
			loggerConPrefix = ConsoleColor::fg_black + ConsoleColor::bg_light_red + loggerPrefix + ConsoleColor::bg_black +
			                  ConsoleColor::fg_light_red;
			break;
		case Type::LOG_FATAL:
			loggerPrefix = "[FATAL]";
			loggerConPrefix =
			    ConsoleColor::fg_black + ConsoleColor::bg_red + loggerPrefix + ConsoleColor::bg_black + ConsoleColor::fg_red;
			break;
	}

	if (m_isOpened)
		m_logStream << dateStr + " " + loggerPrefix + "[" + t_scope + "] " + t_message << std::endl;

	std::cout << ConsoleColor::bg_black + ConsoleColor::fg_light_green + dateStr + ConsoleColor::fg_default +
	                 ConsoleColor::bg_default + " " + loggerConPrefix + "[" + t_scope + "] " + t_message +
	                 ConsoleColor::fg_default + ConsoleColor::bg_default
	          << std::endl;
}