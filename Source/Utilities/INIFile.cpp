#include "INIFile.h"

DronsEngine::INIFile::INIFile() {
    this->isOpened = false;
    this->currentFilePath = "";
}

DronsEngine::INIFile::INIFile(std::string path) {
    this->isOpened = false;
    this->currentFilePath = "";
    this->openINI(path);
}

DronsEngine::INIFile::~INIFile() {

}

void DronsEngine::INIFile::createINI(std::string path) {
    if (this->isOpened) {
        std::cerr << "INI file is already open!" << std::endl;
		exit(1);
    }

    this->currentFile.open(path);
    if (this->currentFile.is_open()) {
        this->currentFile.close();
        std::cerr << "INI file is already exist!" << std::endl;
        exit(1);
    }

    std::ofstream newINIFile;
    newINIFile.open(path, std::ofstream::out | std::ofstream::trunc);
    newINIFile.close();

    this->currentFile.open(path);

	if (!this->currentFile.is_open()) {
		std::cerr << "Failed to open INI file!" << std::endl;
		exit(1);
	}

	this->isOpened = true;
	this->currentFilePath = path;
}

void DronsEngine::INIFile::openINI(std::string path) {
    if (this->isOpened) {
        std::cerr << "INI file is already open!" << std::endl;
		exit(1);
    }

	this->currentFile.open(path);

	if (!this->currentFile.is_open()) {
		std::cerr << "Failed to open INI file!" << std::endl;
		exit(1);
	}

	this->isOpened = true;
	this->currentFilePath = path;

	std::string currentSection = "";

	while(this->currentFile) {
		std::string currentLine;
		std::getline(this->currentFile, currentLine);
		DronsEngine::trim(currentLine);

		if (currentLine[0] == '[' && currentLine[currentLine.length() - 1] == ']' && currentLine.length() > 2) {
			currentSection = currentLine.substr(1, currentLine.length() - 2);
			this->data.insert(std::make_pair(currentSection, std::map<std::string, std::string>()));
		} else if (currentLine[0] != ';' && currentLine[0] != '[' && currentLine != "") {
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
				} else if (i == (int)currentLine.length() - 1) {
					currentValue = currentLine.substr(currentValueStart, i - currentValueStart + 1);
					DronsEngine::trim(currentValue);
					continue;
				} else {
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

			this->data[currentSection].insert(std::make_pair(currentName, currentValue));
		}
	}
}

void DronsEngine::INIFile::saveINI() {
    this->currentFile.close();

    std::ofstream INIFileToWrite;
    INIFileToWrite.open(this->currentFilePath, std::ofstream::out | std::ofstream::trunc);

    std::map<std::string, std::map<std::string, std::string>>::iterator it;
    for(it = this->data.begin(); it != this->data.end(); it++) {
        INIFileToWrite << "[" << it->first << "]" << std::endl;

        std::map<std::string, std::string>::iterator itIn;
        for(itIn = this->data[it->first].begin(); itIn != this->data[it->first].end(); itIn++) {
            INIFileToWrite << itIn->first << " = " << itIn->second << std::endl;
        }

        INIFileToWrite << std::endl;
    }

    INIFileToWrite.close();

    this->currentFile.open(this->currentFilePath);
}

void DronsEngine::INIFile::closeINI() {
    if (!this->isOpened) {
        std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
    }

    this->isOpened = false;
    this->currentFilePath = "";
    this->currentFile.close();
    this->data.clear();
}

void DronsEngine::INIFile::addSection(std::string section) {
    if (!this->isOpened) {
        std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
    }

    if (this->data.find(section) != this->data.end()) {
        std::cerr << "Such a section is already in the INI file!" << std::endl;
		exit(1);
    }

    this->data.insert(std::make_pair(section, std::map<std::string, std::string>()));
}

void DronsEngine::INIFile::deleteSection(std::string section) {
    if (!this->isOpened) {
        std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
    }

    if (this->data.find(section) == this->data.end()) {
        std::cerr << "There is no such section in the INI file!" << std::endl;
		exit(1);
    }

    std::map<std::string, std::map<std::string, std::string>>::iterator it = this->data.find(section);
    this->data.erase(it);
}

void DronsEngine::INIFile::write(std::string section, std::string name, std::string value) {
    if (!this->isOpened) {
        std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
    }

    if (this->data.find(section) == this->data.end()) {
        std::cerr << "There is no such section in the INI file!" << std::endl;
		exit(1);
    }

    if (this->data[section].find(name) != this->data[section].end()) {
        std::map<std::string, std::string>::iterator it = this->data[section].find(name);
        it->second = value;
    }
    else
    {
        this->data[section].insert(std::make_pair(name, value));
    }
}

void DronsEngine::INIFile::erase(std::string section, std::string name) {
    if (!this->isOpened) {
        std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
    }

    if (this->data.find(section) == this->data.end()) {
        std::cerr << "There is no such section in the INI file!" << std::endl;
		exit(1);
    }

    if (this->data[section].find(name) == this->data[section].end()) {
        std::cerr << "There is no such entry in the current section of the INI file!" << std::endl;
		exit(1);
    }

    std::map<std::string, std::string>::iterator it = this->data[section].find(name);
    this->data[section].erase(it);
}

std::string DronsEngine::INIFile::read(std::string section, std::string name) {
    if (!this->isOpened) {
        std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
    }

	if (this->data.find(section) != this->data.end() && this->data[section].find(name) != this->data[section].end())
	    return this->data[section][name];
	else
	    return "";
}
