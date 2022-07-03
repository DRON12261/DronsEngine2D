#pragma once

#include <algorithm>
#include <cctype>
#include <locale>

namespace DronsEngine {
	void leftTrim(std::string& s);
	void rightTrim(std::string& s);
	void trim(std::string& s);
	std::string leftTrimCopy(std::string s);
	std::string rightTrimCopy(std::string s);
	std::string trimCopy(std::string s);
}  // namespace DronsEngine
