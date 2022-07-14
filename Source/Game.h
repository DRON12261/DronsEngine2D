#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <cmath>
#include <stack>

#include "Math/Math.h"
#include "Utilities/INIFile.h"
#include "System/GameLogger.h"
#include "System/GameState.h"

#include "States/SceneState.h"

namespace DronsEngine {
	class Game
	{
	private:
		std::string m_gameTitle = "";
		int m_gameWindowWidth = 0;
		int m_gameWindowHeight = 0;
		int m_gameViewWidth = 1280;
		int m_gameViewHeight = 720;
		int m_gameWindowMode;
		int m_FPSCap = 0;
		int m_physicsFPSCap = 0;

		sf::RenderWindow* mp_gameWindow;
		sf::Clock* mp_gameTime;
		std::stack<GameState*> m_gameStates;

		sf::Time m_elapsedTime;
		sf::Time m_idleLag;
		sf::Time m_physicsLag;
		sf::Time m_msPerIdleFrame;
		sf::Time m_msPerPhysicsFrame;

		int init();
		int initSettings();
		int initWindow();
		int initStates();
		int initObjects();

		int handleEvents();
		int physicsUpdate(const sf::Time& t_deltaTime);
		int update(const sf::Time& t_deltaTime);
		int render(const sf::Time& t_deltaTime);

		int close();

	public:
		Logger GameLog;
		Game(std::string t_gameTitle);
		~Game();
		int run();
	};
}  // namespace DronsEngine

