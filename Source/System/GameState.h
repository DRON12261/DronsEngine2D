#pragma once

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

namespace DronsEngine {
	class GameState
	{
	protected:
		sf::RenderWindow* mp_gameWindow;
		bool m_isQuit = false;

		GameState(sf::RenderWindow* t_gameWindow);

	public:
		const bool& isQuit();

		virtual void startState() = 0;
		virtual void endState() = 0;

		virtual void handleEvents(const sf::Event& event) = 0;
		virtual void physicsUpdate(const sf::Time& t_deltaTime) = 0;
		virtual void update(const sf::Time& t_deltaTime) = 0;
		virtual void render(const sf::Time& t_deltaTime, sf::RenderWindow* t_target = nullptr) = 0;
	};
}  // namespace DronsEngine
