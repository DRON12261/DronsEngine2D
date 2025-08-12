#include "DateTimeUtilities.h"

std::string DronsEngine::getFullDateTime(bool t_includeMilliseconds)
{
	std::chrono::system_clock::time_point currentTimePoint = std::chrono::system_clock::now();
	std::time_t currentTimeT = std::chrono::system_clock::to_time_t(currentTimePoint);
	std::tm localTimeStruct{};
	localtime_s(&localTimeStruct, &currentTimeT);
	std::ostringstream dateTimeStream;

	dateTimeStream << std::put_time(&localTimeStruct, "%d.%m.%Y | %H:%M:%S");

	if (t_includeMilliseconds)
	{
		int milliseconds = static_cast<int>(
		    std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint.time_since_epoch()).count() % 1000);

		dateTimeStream << '.' << std::setw(3) << std::setfill('0') << milliseconds;
	}

	return dateTimeStream.str();
}
