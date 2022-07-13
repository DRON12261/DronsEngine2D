#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <map>
#include <stdio.h>

#include "StringUtilities.h"

namespace DronsEngine {
	class INIFile
	{
	public:
		INIFile();
		//����������� � ����������� ��������� (�� ���������!) ini �����
		INIFile(std::string t_path);
		virtual ~INIFile();

		//������� ����� ini ���� (������ �������� � ���)
		void createINI(std::string t_path);
		//��������� ini ����
		void openINI(std::string t_path);
		//��������� ��������� � ini ����
		void saveINI();
		//��������� ini ����
		void closeINI();
		//��������� ����� ������
		void addSection(std::string t_section);
		//������� ��� ������
		void deleteSection(std::string t_section);
		//������� ����� ������ ��� �������������� ������������
		void write(std::string t_section, std::string t_name, std::string t_value);
		//������� ������
		void erase(std::string t_section, std::string t_name);
		//������ �������� �� ������
		std::string read(std::string t_section, std::string t_name);

	private:
		std::string m_path;
		std::ifstream m_file;
		using iniSection_t = std::map<std::string, std::string>;
		using iniData_t = std::map<std::string, iniSection_t>;
		iniData_t m_data;
		bool m_isOpened;
	};
}  // namespace DronsEngine
