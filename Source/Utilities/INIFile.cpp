#include "INIFile.h"

DronsEngine::INIFile::INIFile()
{
	m_isOpened = false;
	m_path = "";
}

DronsEngine::INIFile::INIFile(std::string t_path)
{
	m_isOpened = false;
	m_path = "";
	openINI(t_path);
}

DronsEngine::INIFile::~INIFile() {}

void DronsEngine::INIFile::createINI(std::string t_path)
{
	if (m_isOpened)
	{
		std::cerr << "INI file is already open!" << std::endl;
		exit(1);
	}

	m_file.open(t_path);
	if (m_file.is_open())
	{
		m_file.close();
		std::cerr << "INI file is already exist!" << std::endl;
		exit(1);
	}

	std::ofstream newINIFile;
	newINIFile.open(t_path, std::ofstream::out | std::ofstream::trunc);
	newINIFile.close();

	m_file.open(t_path);

	if (!m_file.is_open())
	{
		std::cerr << "Failed to open INI file!" << std::endl;
		exit(1);
	}

	m_isOpened = true;
	m_path = t_path;
}

void DronsEngine::INIFile::openINI(std::string t_path)
{
	if (m_isOpened)
	{
		std::cerr << "INI file is already open!" << std::endl;
		exit(1);
	}

	m_file.open(t_path);

	if (!m_file.is_open())
	{
		std::cerr << "Failed to open INI file!" << std::endl;
		exit(1);
	}

	m_isOpened = true;
	m_path = t_path;

	std::string currentSection = "";

	while (m_file)
	{
		std::string currentLine;
		std::getline(m_file, currentLine);
		trim(currentLine);

		if (currentLine[0] == '[' && currentLine[currentLine.length() - 1] == ']' && currentLine.length() > 2)
		{
			currentSection = currentLine.substr(1, currentLine.length() - 2);
			m_data.insert(std::make_pair(currentSection, iniSection_t()));
		}
		else if (currentLine[0] != ';' && currentLine != "")
		{
			std::string currentName = "";
			int currentNameStart = -1;
			std::string currentValue = "";
			int currentValueStart = -1;
			bool isValueNext = false;

			for (int i = 0; i < (int)currentLine.length(); i++)
			{
				if (currentLine[i] == '=')
				{
					isValueNext = true;
					currentName = currentLine.substr(currentNameStart, i);
					trim(currentName);
					continue;
				}
				else if (i == (int)currentLine.length() - 1)
				{
					currentValue = currentLine.substr(currentValueStart, i - currentValueStart + 1);
					trim(currentValue);
					continue;
				}
				else
				{
					if (currentNameStart == -1 && !isValueNext)
					{
						currentNameStart = i;
						continue;
					}

					if (currentValueStart == -1 && isValueNext && currentName != "")
					{
						currentValueStart = i;
						continue;
					}
				}
			}

			if (currentName == "" && currentValue == "")
			{
				std::cerr << "The INI file has incorrect text formatting!" << std::endl;
				exit(1);
			}

			m_data[currentSection].insert(std::make_pair(currentName, currentValue));
		}
	}
}

void DronsEngine::INIFile::saveINI()
{
	m_file.close();

	std::ofstream INIFileToWrite;
	INIFileToWrite.open(m_path, std::ofstream::out | std::ofstream::trunc);

	iniData_t::iterator it;
	for (it = m_data.begin(); it != m_data.end(); it++)
	{
		INIFileToWrite << "[" << it->first << "]" << std::endl;

		iniSection_t::iterator itIn;
		for (itIn = m_data[it->first].begin(); itIn != m_data[it->first].end(); itIn++)
		{
			INIFileToWrite << itIn->first << " = " << itIn->second << std::endl;
		}

		INIFileToWrite << std::endl;
	}

	INIFileToWrite.close();

	m_file.open(m_path);
}

void DronsEngine::INIFile::closeINI()
{
	if (!m_isOpened)
	{
		std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
	}

	m_isOpened = false;
	m_path = "";
	m_file.close();
	m_data.clear();
}

void DronsEngine::INIFile::addSection(std::string t_section)
{
	if (!m_isOpened)
	{
		std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
	}

	if (m_data.find(t_section) != m_data.end())
	{
		std::cerr << "Such a section is already in the INI file!" << std::endl;
		exit(1);
	}

	m_data.insert(std::make_pair(t_section, iniSection_t()));
}

void DronsEngine::INIFile::deleteSection(std::string t_section)
{
	if (!m_isOpened)
	{
		std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
	}

	if (m_data.find(t_section) == m_data.end())
	{
		std::cerr << "There is no such section in the INI file!" << std::endl;
		exit(1);
	}

	iniData_t::iterator it = m_data.find(t_section);
	m_data.erase(it);
}

void DronsEngine::INIFile::write(std::string t_section, std::string t_name, std::string t_value)
{
	if (!m_isOpened)
	{
		std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
	}

	if (m_data.find(t_section) == m_data.end())
	{
		std::cerr << "There is no such section in the INI file!" << std::endl;
		exit(1);
	}

	if (m_data[t_section].find(t_name) != m_data[t_section].end())
	{
		iniSection_t::iterator it = m_data[t_section].find(t_name);
		it->second = t_value;
	}
	else
	{
		m_data[t_section].insert(std::make_pair(t_name, t_value));
	}
}

void DronsEngine::INIFile::erase(std::string t_section, std::string t_name)
{
	if (!m_isOpened)
	{
		std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
	}

	if (m_data.find(t_section) == m_data.end())
	{
		std::cerr << "There is no such section in the INI file!" << std::endl;
		exit(1);
	}

	if (m_data[t_section].find(t_name) == m_data[t_section].end())
	{
		std::cerr << "There is no such entry in the current section of the INI file!" << std::endl;
		exit(1);
	}

	iniSection_t::iterator it = m_data[t_section].find(t_name);
	m_data[t_section].erase(it);
}

std::string DronsEngine::INIFile::read(std::string t_section, std::string t_name)
{
	if (!m_isOpened)
	{
		std::cerr << "The INI file has not been opened yet!" << std::endl;
		exit(1);
	}

	if (m_data.find(t_section) != m_data.end() && m_data[t_section].find(t_name) != m_data[t_section].end())
		return m_data[t_section][t_name];
	else
		return "";
}
