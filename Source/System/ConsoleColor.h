#pragma once

#include <string>

namespace DronsEngine
{
	class ConsoleColor
	{
	public:
		inline static const std::string fg_default = "\033[39m";
		inline static const std::string fg_black = "\033[30m";
		inline static const std::string fg_red = "\033[31m";
		inline static const std::string fg_green = "\033[32m";
		inline static const std::string fg_yellow = "\033[33m";
		inline static const std::string fg_blue = "\033[34m";
		inline static const std::string fg_magenta = "\033[35m";
		inline static const std::string fg_cyan = "\033[36m";
		inline static const std::string fg_white = "\033[37m";
		inline static const std::string fg_light_black = "\033[90m";
		inline static const std::string fg_light_red = "\033[91m";
		inline static const std::string fg_light_green = "\033[92m";
		inline static const std::string fg_light_yellow = "\033[93m";
		inline static const std::string fg_light_blue = "\033[94m";
		inline static const std::string fg_light_magenta = "\033[95m";
		inline static const std::string fg_light_cyan = "\033[96m";
		inline static const std::string fg_light_white = "\033[97m";
		static std::string fg_custom(unsigned short t_red, unsigned short t_green, unsigned short t_blue);
		static std::string fg_custom(unsigned short t_number);

		inline static const std::string bg_default = "\033[49m";
		inline static const std::string bg_black = "\033[40m";
		inline static const std::string bg_red = "\033[41m";
		inline static const std::string bg_green = "\033[42m";
		inline static const std::string bg_yellow = "\033[43m";
		inline static const std::string bg_blue = "\033[44m";
		inline static const std::string bg_magenta = "\033[45m";
		inline static const std::string bg_cyan = "\033[46m";
		inline static const std::string bg_white = "\033[47m";
		inline static const std::string bg_light_black = "\033[100m";
		inline static const std::string bg_light_red = "\033[101m";
		inline static const std::string bg_light_green = "\033[102m";
		inline static const std::string bg_light_yellow = "\033[103m";
		inline static const std::string bg_light_blue = "\033[104m";
		inline static const std::string bg_light_magenta = "\033[105m";
		inline static const std::string bg_light_cyan = "\033[106m";
		inline static const std::string bg_light_white = "\033[107m";
		static std::string bg_custom(unsigned short t_red, unsigned short t_green, unsigned short t_blue);
		static std::string bg_custom(unsigned short t_number);
	};
}  // namespace DronsEngine
