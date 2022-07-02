#include "INIFile.h"

DronsEngine::INIFile::INIFile() {
	isOpened = false;
	currentFilePath = "";
}

DronsEngine::INIFile::INIFile(std::string path) {
	isOpened = false;
	currentFilePath = "";
	openINI(path);
}

DronsEngine::INIFile::~INIFile() {

}

void DronsEngine::INIFile::createINI(std::string path) {
	if (isOpened) {
		std::cerr << "INI file is already open!" << std::endl;
		exit(1);
	}

	currentFile.open(path);
	if (currentFile.is_open()) {
		currentFile.close();
		std::cerr << "INI file is already exist!" << std::endl;
		exit(1);
	}

	std::ofstream newINIFile;
	newINIFile.open(path, std::ofstream::out | std::ofstream::trunc);
	newINIFile.close();

	currentFile.open(path);

	if (!currentFile.is_open()) {
		std::cerr << "Failed to open INI file!" << std::endl;
		exit(1);
	}

	isOpened = true;
	currentFilePath = path;
}

void DronsEngine::INIFile::openINI(std::string path) {
	if (isOpened) {
		std::cerr << "INI file is already open!" << std::endl;
		exit(1);
	}

	currentFile.open(path);

	if (!currentFile.is_open()) {
		std::cerr << "Failed to open INI file!" << std::endl;
		exit(1);
	}

	isOpened = true;
	currentFilePath = path;

	std::string currentSection = "";

	while (currentFile) {
		std::string currentLine;
		std::getline(currentFile, currentLine);
		DronsEngine::trim(currentLine);

		if (currentLine[0] == '[' && currentLine[currentLine.length() - 1] == ']' && currentLine.length() > 2) {
			currentSection = currentLine.substr(1, currentLine.length() - 2);
			data.insert(std::make_pair(currentSection, iniSection_t()));
		}
		else if (currentLine[0] != ';' && currentLine != "") {
			std::string currentName = "";
			int currentNameStart = -1;
			std::string currentValue = "";
			int currentValueStart = -1;
			bool isValueNext = false;

			for (int i = 0; i < (int)currentLine.length(); i++) {
				if (currentLine[i] == '=') {
					isValueNext = true;
					currentName = currentLine.substr(currentNameStart, i);
					DronsEngine::trim(currentName);
					continue;
				}
				else if (i == (int)currentLine.length() - 1) {
					currentValue = currentLine.substr(currentValueStart, i - currentValueStart + 1);
					DronsEngine::trim(currentValue);
					continue;
				}
				else {
					if (currentNameStart == -1 && !isValueNext) {
						currentNameStart = i;
						continue;
					}

					if (currentValueStart == -1 && isValueNext && currentName != "") {
						currentValueStart = i;
						continue;
					}
				}
			}

			if (currentName == "" && currentValue == "") {
				std::cerr << "The INI file has incorrect text formatting!" << std::endl;
				exit(1);
			}

			data[currentSection].insert(std::make_pair(currentName, currentValue));
		}
	}
}

void DronsEngine::INIFile::saveINI() {
	currentFile.close();

	std::ofstream INIFileToWrite;
	INIFileToWrite.open(currentFilePath, std::ofstream::out | std::ofstream::trunc);

	iniData_t::iterator it;
	for (it = data.begin(); it != data.end(); it++) {
		INIFileToWrite << "[" << it->first << "]" << std::endl;

		iniSection_t::iterator itIn;
		for (itIn = data[it->first].begin(); itIn != data[it->first].end(); itIn++) {
			INIFileToWrite << itIn->first << " = " << itIn->second << std::endl;
		}

		INIFileToWrite << std::endl;
	}

	INIFileToWrite.close();

	currentFile.open(currentFilePath);
}

void DronsEngine::INIFile::closeINI() {
	if (!isOpened) {
		std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
	}

	isOpened = false;
	currentFilePath = "";
	currentFile.close();
	data.clear();
}

void DronsEngine::INIFile::addSection(std::string section) {
	if (!isOpened) {
		std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
	}

	if (data.find(section) != data.end()) {
		std::cerr << "Such a section is already in the INI file!" << std::endl;
		exit(1);
	}

	data.insert(std::make_pair(section, std::map<std::string, std::string>()));
}

void DronsEngine::INIFile::deleteSection(std::string section) {
	if (!isOpened) {
		std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
	}

	if (data.find(section) == data.end()) {
		std::cerr << "There is no such section in the INI file!" << std::endl;
		exit(1);
	}

	iniData_t::iterator it = data.find(section);
	data.erase(it);
}

void DronsEngine::INIFile::write(std::string section, std::string name, std::string value) {
	if (!isOpened) {
		std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
	}

	if (data.find(section) == data.end()) {
		std::cerr << "There is no such section in the INI file!" << std::endl;
		exit(1);
	}

	if (data[section].find(name) != data[section].end()) {
		iniSection_t::iterator it = data[section].find(name);
		it->second = value;
	}
	else
	{
		data[section].insert(std::make_pair(name, value));
	}
}

void DronsEngine::INIFile::erase(std::string section, std::string name) {
	if (!isOpened) {
		std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
	}

	if (data.find(section) == data.end()) {
		std::cerr << "There is no such section in the INI file!" << std::endl;
		exit(1);
	}

	if (data[section].find(name) == data[section].end()) {
		std::cerr << "There is no such entry in the current section of the INI file!" << std::endl;
		exit(1);
	}

	iniSection_t::iterator it = data[section].find(name);
	data[section].erase(it);
}

std::string DronsEngine::INIFile::read(std::string section, std::string name) {
	if (!isOpened) {
		std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
	}

	if (data.find(section) != data.end() && data[section].find(name) != data[section].end())
		return data[section][name];
	else
		return "";
}
