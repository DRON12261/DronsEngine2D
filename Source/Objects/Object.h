#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace DronsEngine
{
	class Object
	{
	public:
		Object();
		virtual ~Object();

		virtual void update(sf::Time t_deltaTime);
		virtual void physicsUpdate(sf::Time t_deltaTime);
		virtual void render(sf::Time t_deltaTime);

	protected:
	private:
	};
}  // namespace DronsEngine
