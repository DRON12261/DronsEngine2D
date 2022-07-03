#include "Logger.h"

DronsEngine::Logger::Logger(std::string path)
{
	isOpened = false;
	path = "";
	open(path);
}

DronsEngine::Logger::Logger()
{
	isOpened = false;
	path = "";
}

DronsEngine::Logger::~Logger()
{
	close();
}

void DronsEngine::Logger::open(std::string path)
{
	logStream.open(path, std::ofstream::out | std::ofstream::app);

	if (!logStream.is_open())
	{
		std::cerr << "Failed to open log file \"" << path << "\"." << std::endl;
		exit(1);
	}

	isOpened = true;
	this->path = path;
}

void DronsEngine::Logger::close()
{
	if (logStream.is_open())
	{
		logStream << std::endl << std::endl << std::endl;
		logStream.close();
	}

	isOpened = false;
	path = "";
}

bool DronsEngine::Logger::isOpen()
{
	return isOpened;
}

void DronsEngine::Logger::log(std::string message)
{
	auto t = std::time(nullptr);
	std::tm tm{};
	localtime_s(&tm, &t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "[%d.%m.%Y | %H:%M:%S]");
	auto dateStr = oss.str();

	logStream << dateStr << message << std::endl;
}

void DronsEngine::Logger::logWarning(std::string message)
{
	auto t = std::time(nullptr);
	std::tm tm{};
	localtime_s(&tm, &t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "[%d.%m.%Y | %H:%M:%S]");
	auto dateStr = oss.str();

	logStream << dateStr << "[WARNING]" << message << std::endl;
}

void DronsEngine::Logger::logError(std::string message)
{
	auto t = std::time(nullptr);
	std::tm tm{};
	localtime_s(&tm, &t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "[%d.%m.%Y | %H:%M:%S]");
	auto dateStr = oss.str();

	logStream << dateStr << "[ERROR]" << message << std::endl;
}