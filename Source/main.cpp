#include "Game.h"

/*

--++--viewport (hud ��� ������ ����������� ������)
------ini
inputhandler
������ � ����� �������
�������
������� ui �������� (bar, button, image, text, rectangle)
�������� ��� ��������� ������ ��������
������� ���������� �������� �� �������
��������� ����� �� ���� ������
������� � ���������������
��������� ����� � �������� (lua)

*/

int main() {
	DronsEngine::Game MyGame("DronsEngine Game");
	return MyGame.run();
}
