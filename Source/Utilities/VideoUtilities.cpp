#include "VideoUtilities.h"

unsigned int DronsEngine::getMonitorRefreshRate()
{
	// �������� ������� ���������� �������� �����
	//sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	//return desktopMode.refreshRate;
	return 60;  // ���������� �������� �� ���������, ���� �� ������� �������� ����������
}
