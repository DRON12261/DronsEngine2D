#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <stacktrace>
#include <chrono>

#include "ConsoleColor.h"
#include "FileSystem.h"
#include "../Utilities/DateTimeUtilities.h"

namespace DronsEngine
{
	class Logger
	{
	private:
		bool m_isOpened;
		std::ofstream m_logStream;
		std::string m_path;

	public:
		enum Type
		{
			LOG_INFO = 0, // Только информация
			LOG_DEBUG, // Дополнительная информация для отладки
			LOG_WARNING, // Предупреждение, некритичное для работоспособности
			LOG_ERROR, // Ошибка, не препятствующая работоспособности
			LOG_FATAL // Ошибка, блокирующая работоспособность
		};

		Logger();
		Logger(std::string t_path);
		~Logger();
		void open(std::string t_path);
		void close();
		bool isOpen() const;
		void log(std::string t_message, Type t_type = Type::LOG_INFO, std::string t_scope = "");
	};
}  // namespace DronsEngine
