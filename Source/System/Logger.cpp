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
	if (!isDirectoryExists(t_path))
	{
		if (!createDirectoryForFile(t_path))
		{
			std::cerr << "Failed to create directory for log file \"" << t_path << "\"." << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	m_logStream.open(t_path, std::ofstream::out | std::ofstream::app);

	if (!m_logStream.is_open())
	{
		std::cerr << "Failed to open log file \"" << t_path << "\"." << std::endl;
		exit(EXIT_FAILURE);
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

	std::string dateStr = "[" + getFullDateTime(true) + "]";

	std::string loggerConPrefix = "";
	std::string loggerPrefix = "";

	std::ostringstream stackTraceStream;
	std::stacktrace currentStackTrace = std::stacktrace::current();
	for (std::size_t i = 2; i < currentStackTrace.size(); ++i)
	{
		stackTraceStream << ">" << i - 2 << " " << currentStackTrace[i] << std::endl;
	}
	std::string stackTraceStr = stackTraceStream.str();

	switch (t_type)
	{
		case Type::LOG_INFO:
			loggerPrefix = dateStr + " " + "[INFO ]";
			loggerConPrefix = ConsoleColor::fg_black + ConsoleColor::bg_light_green + loggerPrefix + ConsoleColor::bg_black +
			                  ConsoleColor::fg_light_green;
			break;
		case Type::LOG_DEBUG:
			loggerPrefix = dateStr + " " + "[DEBUG]";
			loggerConPrefix = ConsoleColor::fg_black + ConsoleColor::bg_light_blue + loggerPrefix + ConsoleColor::bg_black +
			                  ConsoleColor::fg_light_blue;
			break;
		case Type::LOG_WARNING:
			loggerPrefix = dateStr + " " + "[WARN ]";
			loggerConPrefix = ConsoleColor::fg_black + ConsoleColor::bg_yellow + loggerPrefix + ConsoleColor::bg_black +
			                  ConsoleColor::fg_light_yellow;
			break;
		case Type::LOG_ERROR:
			loggerPrefix = dateStr + " " + "[ERROR]";
			loggerConPrefix = ConsoleColor::fg_black + ConsoleColor::bg_light_red + loggerPrefix + ConsoleColor::bg_black +
			                  ConsoleColor::fg_light_red;
			break;
		case Type::LOG_FATAL:
			loggerPrefix = dateStr + " " + "[FATAL]";
			loggerConPrefix =
			    ConsoleColor::fg_black + ConsoleColor::bg_red + loggerPrefix + ConsoleColor::bg_black + ConsoleColor::fg_red;
			break;
	}

	if (m_isOpened)
	{
		m_logStream << loggerPrefix + "[" + t_scope + "] " + t_message << std::endl;

		if (t_type == Type::LOG_ERROR || t_type == Type::LOG_FATAL)
		{
			m_logStream << stackTraceStr;
		}
	}

	std::cout << loggerConPrefix + "[" + t_scope + "] " + t_message + ConsoleColor::fg_default + ConsoleColor::bg_default
	          << std::endl;

	if (t_type == Type::LOG_ERROR || t_type == Type::LOG_FATAL)
	{
		std::cout << ConsoleColor::bg_black +
		                 (t_type == Type::LOG_ERROR ? ConsoleColor::fg_light_red : ConsoleColor::fg_red) + stackTraceStr +
		                 ConsoleColor::fg_default + ConsoleColor::bg_default
		          << std::endl;
	}
}