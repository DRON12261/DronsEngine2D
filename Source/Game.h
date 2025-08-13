#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <ENet/enet.h>

#include <iostream>
#include <string>
#include <cmath>
#include <stack>
#include <thread>
#include <mutex>
#include <filesystem>
//#include <exception>
#include <chrono>

#include "Math/Math.h"
#include "Utilities/INIFile.h"
#include "Utilities/VideoUtilities.h"
#include "System/GameLogger.h"
#include "System/GameState.h"

#include "States/SceneState.h"

namespace DronsEngine {

	class Game
	{
	private:
		std::string m_gameTitle = "";
		unsigned int m_gameWindowWidth = 0;
		unsigned int m_gameWindowHeight = 0;
		unsigned int m_gameViewWidth = 1280;
		unsigned int m_gameViewHeight = 720;
		int m_gameWindowStyle = sf::Style::Default;

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

		void init();
		void initSettings();
		void initWindow();
		void initNetwork();
		void initStates();
		void initObjects();

		void handleEvents();
		void physicsUpdate(const sf::Time& t_deltaTime);
		void update(const sf::Time& t_deltaTime);
		void render(const sf::Time& t_deltaTime);

		void close();

	public:
		Logger GameLog;
		Game(std::string t_gameTitle);
		~Game();
		void run();
	};
}  // namespace DronsEngine
