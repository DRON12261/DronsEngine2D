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
		INIFile(std::string path);
		virtual ~INIFile();

		//создает новый ini файл (дальше работаем с ним)
		void createINI(std::string path);
		//открывает ini файл
		void openINI(std::string path);
		//сохраняет изменения в ini файл
		void saveINI();
		//закрывает ini файл
		void closeINI();
		//добавляет новую секцию
		void addSection(std::string section);
		//удаляет всю секцию
		void deleteSection(std::string section);
		//создает новую запись или перезаписывает существующую
		void write(std::string section, std::string name, std::string value);
		//удаляет запись
		void erase(std::string section, std::string name);
		//читает значение из записи
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
