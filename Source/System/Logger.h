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
			LOG_INFO = 0, // ������ ����������
			LOG_DEBUG, // �������������� ���������� ��� �������
			LOG_WARNING, // ��������������, ����������� ��� �����������������
			LOG_ERROR, // ������, �� �������������� �����������������
			LOG_FATAL // ������, ����������� �����������������
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
