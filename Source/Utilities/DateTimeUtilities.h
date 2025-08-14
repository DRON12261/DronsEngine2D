#pragma once

#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace DronsEngine
{
	std::string getFullDateTime(bool t_includeMilliseconds = false);
}  // namespace DronsEngine