#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <cmath>

#include "Math/Math.h"
#include "Utilities/INIFile.h"

namespace DronsEngine {
class Game {
  private:
	sf::CircleShape *shape;
	sf::CircleShape *mouseShape;

	std::string gameTitle = "";
	int gameWindowWidth = 0;
	int gameWindowHeight = 0;
	int gameViewWidth = 1280;
	int gameViewHeight = 720;
	int gameWindowMode;
	sf::RenderWindow *gameWindow;
	sf::Clock *gameTime;
	sf::Time elapsedTime;
	sf::Time idleLag;
	sf::Time physicsLag;
	int FPSCap = 0;
	int PhysicsFPSCap = 0;
	sf::Time msPerIdleFrame;
	sf::Time msPerPhysicsFrame;

	int init();
	int handleEvents();
	int physicsUpdate(sf::Time deltaTime);
	int update(sf::Time deltaTime);
	int render(sf::Time deltaTime);

  public:
	Game(std::string gameTitle);
	int run();
};
}

#endif
