#include "VideoUtilities.h"

unsigned int DronsEngine::getMonitorRefreshRate()
{
	// Получаем текущий видеорежим рабочего стола
	//sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	//return desktopMode.refreshRate;
	return 60;  // Возвращаем значение по умолчанию, если не удалось получить видеорежим
}
