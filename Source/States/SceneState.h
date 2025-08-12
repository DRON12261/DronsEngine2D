#pragma once

#include "SFML/System.hpp"

#include "../System/GameState.h"
#include "../Math/Math.h"
#include "../System/GameLogger.h"

namespace DronsEngine {
	class SceneState : public GameState
	{
	private:
		sf::CircleShape* m_shape;
		sf::CircleShape* m_mouseShape;

	public:
		SceneState(sf::RenderWindow* t_gameWindow);

		void startState() override;
		void endState() override;

		void handleEvents(const std::optional<sf::Event>& event) override;
		void physicsUpdate(const sf::Time& t_deltaTime) override;
		void update(const sf::Time& t_deltaTime) override;
		void render(const sf::Time& t_deltaTime, sf::RenderWindow* t_target = nullptr) override;
	};
}  // namespace DronsEngine
