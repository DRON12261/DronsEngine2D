#pragma once

#include <algorithm>
#include <cctype>
#include <locale>

namespace DronsEngine
{
	void leftTrim(std::string& t_string);
	void rightTrim(std::string& t_string);
	void trim(std::string& t_string);
}  // namespace DronsEngine
