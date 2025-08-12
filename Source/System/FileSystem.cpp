#include "FileSystem.h"

bool DronsEngine::createDirectory(std::string t_path)
{
	return std::filesystem::create_directory(t_path);
}

bool DronsEngine::createDirectoryForFile(std::string t_path)
{
	std::filesystem::path dir = std::filesystem::path(t_path).parent_path();

	return std::filesystem::create_directory(dir);
}

bool DronsEngine::isFileExists(std::string t_path)
{
	return std::filesystem::exists(t_path);
}

bool DronsEngine::isDirectoryExists(std::string t_path)
{
	std::filesystem::path dir = t_path;

	if (!std::filesystem::is_directory(t_path))
		dir = std::filesystem::path(t_path).parent_path();

	return std::filesystem::exists(dir);
}
