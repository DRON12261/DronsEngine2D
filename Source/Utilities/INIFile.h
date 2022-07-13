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
		//конструктор с последующим открытием (не созданием!) ini файла
		INIFile(std::string t_path);
		virtual ~INIFile();

		//создает новый ini файл (дальше работаем с ним)
		void createINI(std::string t_path);
		//открывает ini файл
		void openINI(std::string t_path);
		//сохраняет изменения в ini файл
		void saveINI();
		//закрывает ini файл
		void closeINI();
		//добавляет новую секцию
		void addSection(std::string t_section);
		//удаляет всю секцию
		void deleteSection(std::string t_section);
		//создает новую запись или перезаписывает существующую
		void write(std::string t_section, std::string t_name, std::string t_value);
		//удаляет запись
		void erase(std::string t_section, std::string t_name);
		//читает значение из записи
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
