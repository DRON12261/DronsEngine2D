#include "StringUtilities.h"

void DronsEngine::leftTrim(std::string &s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
}

void DronsEngine::rightTrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
	}).base(), s.end());
}

void DronsEngine::trim(std::string &s) {
	DronsEngine::leftTrim(s);
	DronsEngine::rightTrim(s);
}

std::string DronsEngine::leftTrimCopy(std::string s) {
	DronsEngine::leftTrim(s);
	return s;
}

std::string DronsEngine::rightTrimCopy(std::string s) {
	DronsEngine::rightTrim(s);
	return s;
}

std::string DronsEngine::trimCopy(std::string s) {
	DronsEngine::trim(s);
	return s;
}
