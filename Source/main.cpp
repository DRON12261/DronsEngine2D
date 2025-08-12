#include "Game.h"

void terminateHandler()
{
	try
	{
		auto eptr = std::current_exception();
		if (eptr)
		{
			std::rethrow_exception(eptr);
		}
	}
	catch (const std::exception& ex)
	{
		DronsEngine::GameLogger::log("Runtime error! " + std::string(ex.what()), DronsEngine::Logger::Type::LOG_FATAL, "Core");
	}
	catch (const std::string& msg)
	{
		DronsEngine::GameLogger::log("Runtime error! " + msg, DronsEngine::Logger::Type::LOG_FATAL, "Core");
	}
	catch (const char* msg)
	{
		DronsEngine::GameLogger::log(std::string("Runtime error! ") + msg, DronsEngine::Logger::Type::LOG_FATAL, "Core");
	}
	catch (int code)
	{
		DronsEngine::GameLogger::log("Runtime error! Exception code: " + std::to_string(code), DronsEngine::Logger::Type::LOG_FATAL, "Core");
	}
	catch (...)
	{
		DronsEngine::GameLogger::log("Unknown runtime error!", DronsEngine::Logger::Type::LOG_FATAL, "Core");
	}

	exit(EXIT_FAILURE);
}

int main()
{
	std::set_terminate(terminateHandler);

	DronsEngine::Game DronsGame("DronsEngine Game");
	DronsGame.run();

	return(EXIT_SUCCESS);
}

// Code-style convention here:
// https://lefticus.gitbooks.io/cpp-best-practices/content/03-Style.html

// SFML version - 3.0.0