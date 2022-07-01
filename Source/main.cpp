#include "Game.h"

/*

--++--viewport (hud под разные соотношения сторон)
------ini
inputhandler
работа с медиа файлами
колизии
простые ui элементы (bar, button, image, text, rectangle)
подумать над хранением данных активных
система деативации обьектов за экраном
прогрузка карты из кучи тайлов
попытка в многопоточность
поддержка модов и скриптов (lua)

*/

int main() {
	DronsEngine::Game MyGame("DronsEngine Game");
	return MyGame.run();
}
