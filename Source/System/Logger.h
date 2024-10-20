#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>

#include "ConsoleColor.h"

namespace DronsEngine {
	class Logger
	{
	private:
		bool m_isOpened;
		std::ofstream m_logStream;
		std::string m_path;
		
	public:
		enum Type {
			INFO = 0, // ������ ����������
			DEBUG, // �������������� ���������� ��� �������
			WARNING, // ��������������, ����������� ��� �����������������
			ERROR, // ������, �� �������������� �����������������
			FATAL // ������, ����������� �����������������
		};

		Logger();
		Logger(std::string t_path);
		~Logger();
		void open(std::string t_path);
		void close();
		bool isOpen() const;
		void log(std::string t_message, Type t_type = Type::INFO, std::string t_scope = "");
	};
}  // namespace DronsEngine
