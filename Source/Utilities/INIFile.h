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
		INIFile(std::string path);
		virtual ~INIFile();

		//������� ����� ini ���� (������ �������� � ���)
		void createINI(std::string path);
		//��������� ini ����
		void openINI(std::string path);
		//��������� ��������� � ini ����
		void saveINI();
		//��������� ini ����
		void closeINI();
		//��������� ����� ������
		void addSection(std::string section);
		//������� ��� ������
		void deleteSection(std::string section);
		//������� ����� ������ ��� �������������� ������������
		void write(std::string section, std::string name, std::string value);
		//������� ������
		void erase(std::string section, std::string name);
		//������ �������� �� ������
		std::string read(std::string section, std::string name);

	protected:
	private:
		std::string currentFilePath;
		std::ifstream currentFile;
		using iniSection_t = std::map<std::string, std::string>;
		using iniData_t = std::map<std::string, iniSection_t>;
		iniData_t data;
		bool isOpened;
	};
}  // namespace DronsEngine
