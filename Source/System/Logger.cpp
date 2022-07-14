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

bool DronsEngine::Logger::isOpen()
{
	return m_isOpened;
}

void DronsEngine::Logger::log(std::string t_message)
{
	auto t = std::time(nullptr);
	std::tm tm{};
	localtime_s(&tm, &t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "[%d.%m.%Y | %H:%M:%S]");
	auto dateStr = oss.str();

	m_logStream << dateStr << " " << t_message << std::endl;

	std::cout << ConsoleColor::bg_black << ConsoleColor::fg_light_green << dateStr << ConsoleColor::fg_default
	          << ConsoleColor::bg_default << " " << ConsoleColor::fg_black << ConsoleColor::bg_blue << "[  INFO   ]"
	          << ConsoleColor::fg_default << ConsoleColor::bg_default << " " << ConsoleColor::bg_black
	          << ConsoleColor::fg_light_blue << t_message << ConsoleColor::fg_default << ConsoleColor::bg_default
	          << std::endl;
}

void DronsEngine::Logger::logWarning(std::string t_message)
{
	auto t = std::time(nullptr);
	std::tm tm{};
	localtime_s(&tm, &t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "[%d.%m.%Y | %H:%M:%S]");
	auto dateStr = oss.str();

	m_logStream << dateStr << "[ WARNING ] " << t_message << std::endl;
	std::cout << ConsoleColor::bg_black << ConsoleColor::fg_light_green << dateStr << ConsoleColor::fg_default
	          << ConsoleColor::bg_default << " " << ConsoleColor::fg_black << ConsoleColor::bg_yellow << "[ WARNING ]"
	          << ConsoleColor::fg_default << ConsoleColor::bg_default << " " << ConsoleColor::bg_black
	          << ConsoleColor::fg_light_yellow << t_message << ConsoleColor::fg_default << ConsoleColor::bg_default
	          << std::endl;
}

void DronsEngine::Logger::logError(std::string t_message)
{
	auto t = std::time(nullptr);
	std::tm tm{};
	localtime_s(&tm, &t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "[%d.%m.%Y | %H:%M:%S]");
	auto dateStr = oss.str();

	m_logStream << dateStr << "[  ERROR  ] " << t_message << std::endl;
	std::cout << ConsoleColor::bg_black << ConsoleColor::fg_light_green << dateStr << ConsoleColor::fg_default
	          << ConsoleColor::bg_default << " " << ConsoleColor::fg_black << ConsoleColor::bg_red << "[  ERROR  ]"
	          << ConsoleColor::fg_default << ConsoleColor::bg_default << " " << ConsoleColor::bg_black
	          << ConsoleColor::fg_light_red << t_message << ConsoleColor::fg_default << ConsoleColor::bg_default
	          << std::endl;
}