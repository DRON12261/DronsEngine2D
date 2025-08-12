#include "GameState.h"

DronsEngine::GameState::GameState(sf::RenderWindow* t_gameWindow)
{
	mp_gameWindow = t_gameWindow;
}

const bool& DronsEngine::GameState::isQuit() const
{
	return m_isQuit;
}
