#pragma once

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
#include "System/GameLogger.h"

namespace DronsEngine {
	class Game
	{
	private:
		sf::CircleShape* m_shape;
		sf::CircleShape* m_mouseShape;

		std::string m_gameTitle = "";
		int m_gameWindowWidth = 0;
		int m_gameWindowHeight = 0;
		int m_gameViewWidth = 1280;
		int m_gameViewHeight = 720;
		int m_gameWindowMode;
		sf::RenderWindow* mp_gameWindow;
		sf::Clock* mp_gameTime;
		sf::Time m_elapsedTime;
		sf::Time m_idleLag;
		sf::Time m_physicsLag;
		int m_FPSCap = 0;
		int m_physicsFPSCap = 0;
		sf::Time m_msPerIdleFrame;
		sf::Time m_msPerPhysicsFrame;

		int init();
		int handleEvents();
		int physicsUpdate(sf::Time deltaTime);
		int update(sf::Time deltaTime);
		int render(sf::Time deltaTime);

	public:
		DronsEngine::Logger GameLog;
		Game(std::string gameTitle);
		int run();
	};
}  // namespace DronsEngine

