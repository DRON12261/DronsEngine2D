#include "ConsoleColor.h"

std::string DronsEngine::ConsoleColor::fg_custom(unsigned short t_red, unsigned short t_green, unsigned short t_blue)
{
	if (t_red > 255)
		t_red = 255;
	if (t_green > 255)
		t_green = 255;
	if (t_blue > 255)
		t_blue = 255;
	return "\033[38;2;" + std::to_string(t_red) + ";" + std::to_string(t_green) + ";" + std::to_string(t_blue) + "m";
}

std::string DronsEngine::ConsoleColor::fg_custom(unsigned short t_number)
{
	if (t_number > 255)
		t_number = 255;
	return "\033[38;5;" + std::to_string(t_number) + "m";
}

std::string DronsEngine::ConsoleColor::bg_custom(unsigned short t_red, unsigned short t_green, unsigned short t_blue)
{
	if (t_red > 255)
		t_red = 255;
	if (t_green > 255)
		t_green = 255;
	if (t_blue > 255)
		t_blue = 255;
	return "\033[48;2;" + std::to_string(t_red) + ";" + std::to_string(t_green) + ";" + std::to_string(t_blue) + "m";
}

std::string DronsEngine::ConsoleColor::bg_custom(unsigned short t_number)
{
	if (t_number > 255)
		t_number = 255;
	return "\033[48;5;" + std::to_string(t_number) + "m";
}
