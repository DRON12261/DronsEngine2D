#include "StringUtilities.h"

void DronsEngine::leftTrim(std::string& t_string)
{
	t_string.erase(t_string.begin(),
	               std::find_if(t_string.begin(), t_string.end(), [](unsigned char ch) { return !std::isspace(ch); }));
}

void DronsEngine::rightTrim(std::string& t_string)
{
	t_string.erase(
	    std::find_if(t_string.rbegin(), t_string.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(),
	    t_string.end());
}

void DronsEngine::trim(std::string& t_string)
{
	DronsEngine::leftTrim(t_string);
	DronsEngine::rightTrim(t_string);
}
