#include "SceneState.h"

DronsEngine::SceneState::SceneState(sf::RenderWindow* t_gameWindow) : GameState(t_gameWindow)
{
	m_shape = new sf::CircleShape(50.f);
	m_mouseShape = new sf::CircleShape(20.f);
}

void DronsEngine::SceneState::startState()
{
	GameLogger::log("Starting Scene state...", Logger::Type::LOG_DEBUG, "State System");

	//  Initialization test objects
	m_shape->setFillColor(sf::Color::Green);
	m_shape->setOrigin(m_shape->getRadius(), m_shape->getRadius());
	m_shape->setPosition(mp_gameWindow->getSize().x / static_cast<float>(2),
	                     mp_gameWindow->getSize().y / static_cast<float>(2));
	m_mouseShape->setFillColor(sf::Color::Yellow);
	m_mouseShape->setOrigin(m_mouseShape->getRadius(), m_mouseShape->getRadius());
}

void DronsEngine::SceneState::endState()
{
	GameLogger::log("Ending Scene state...", Logger::Type::LOG_DEBUG, "State System");

	delete m_mouseShape;
	delete m_shape;
}

void DronsEngine::SceneState::handleEvents(const sf::Event& event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_isQuit = true;
	}
}

void DronsEngine::SceneState::physicsUpdate(const sf::Time& t_deltaTime)
{
	// Getting mouse position
	sf::Vector2i pixelMousePos = sf::Mouse::getPosition(*mp_gameWindow);
	sf::Vector2f viewMousePos = mp_gameWindow->mapPixelToCoords(pixelMousePos);

	if (isCirclesCollide(*m_shape, *m_mouseShape))
	{
		if (isCircleAndPointCollide(viewMousePos, m_shape->getPosition(), m_shape->getRadius() - m_mouseShape->getRadius()))
		{
			m_shape->setFillColor(sf::Color::Red);
			m_mouseShape->setFillColor(sf::Color::Magenta);
			GameLogger::log("EVENT 1!", Logger::Type::LOG_DEBUG, "Physics Engine");
		}
		else if (isCircleAndPointCollide(viewMousePos, *m_shape))
		{
			m_shape->setFillColor(sf::Color::White);
			m_mouseShape->setFillColor(sf::Color::Black);
			GameLogger::log("EVENT 2!", Logger::Type::LOG_DEBUG, "Physics Engine");
		}
		else
		{
			m_shape->setFillColor(sf::Color::Cyan);
			m_mouseShape->setFillColor(sf::Color::Red);
			GameLogger::log("EVENT 3!", Logger::Type::LOG_DEBUG, "Physics Engine");
		}
	}
	else
	{
		m_shape->setFillColor(sf::Color::Green);
		m_mouseShape->setFillColor(sf::Color::Yellow);
	}
}

void DronsEngine::SceneState::update(const sf::Time& t_deltaTime)
{
	// Getting mouse position
	sf::Vector2i pixelMousePos = sf::Mouse::getPosition(*mp_gameWindow);
	sf::Vector2f viewMousePos = mp_gameWindow->mapPixelToCoords(pixelMousePos);

	m_mouseShape->setPosition(viewMousePos);
}

void DronsEngine::SceneState::render(const sf::Time& t_deltaTime, sf::RenderWindow* t_target)
{
	mp_gameWindow->draw(*m_shape);
	mp_gameWindow->draw(*m_mouseShape);
}
