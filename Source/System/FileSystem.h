#pragma once

#include <iostream>
#include <filesystem>
#include <string>

namespace DronsEngine
{
	bool createDirectory(std::string t_path);
	bool createDirectoryForFile(std::string t_path);
	bool isFileExists(std::string t_path);
	bool isDirectoryExists(std::string t_path);
}  // namespace DronsEngine