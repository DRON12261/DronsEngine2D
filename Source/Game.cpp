#include "Game.h"

DronsEngine::Game::Game(std::string gameTitle)
{
	DronsEngine::GameLogger::log("Launching \"" + gameTitle + "\" ...");
	this->m_gameTitle = gameTitle;
	mp_gameWindow = new sf::RenderWindow();
}

int DronsEngine::Game::run()
{
	init();

	DronsEngine::GameLogger::log("Start game loop...");
	while (mp_gameWindow->isOpen())
	{
		//  Calculating frametime
		m_elapsedTime = mp_gameTime->restart();
		m_idleLag += m_elapsedTime;
		m_physicsLag += m_elapsedTime;

		//  Handling events
		handleEvents();

		//  Physics loop
		if (m_physicsLag > m_msPerPhysicsFrame)
		{
			physicsUpdate(m_physicsLag);
			m_physicsLag -= m_msPerPhysicsFrame;
		}

		// Idle and render loop
		if (m_idleLag > m_msPerIdleFrame)
		{
			update(m_idleLag);
			render(m_idleLag);
			m_idleLag -= m_msPerIdleFrame;
		}
	}

	return 0;
}

int DronsEngine::Game::init()
{
	DronsEngine::GameLogger::log("Initialization...");

	//  Open settings.ini
	DronsEngine::INIFile INIreader("Configs/Settings.ini");

	//  Load settings
	std::string readedString = INIreader.read("Video", "Width");
	m_gameWindowWidth = readedString != "" ? std::stoi(readedString) : sf::VideoMode::getDesktopMode().width;
	readedString = INIreader.read("Video", "Height");
	m_gameWindowHeight = readedString != "" ? std::stoi(readedString) : sf::VideoMode::getDesktopMode().height;
	readedString = INIreader.read("Video", "FPSCap");
	m_FPSCap = readedString != "" ? std::stoi(readedString) : 60;
	readedString = INIreader.read("Other", "PhysicsFPSCap");
	m_physicsFPSCap = readedString != "" ? std::stoi(readedString) : 30;
	readedString = INIreader.read("Video", "Mode");
	switch (std::stoi(readedString))
	{
		case 0:
			m_gameWindowMode = sf::Style::Titlebar | sf::Style::Close;
			break;
		case 1:
			m_gameWindowMode = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;
			break;
		case 2:
			m_gameWindowMode = sf::Style::Fullscreen;
			break;
		case 3:
			m_gameWindowMode = sf::Style::None;
			break;
	}
	INIreader.closeINI();

	//  Prepare main view
	sf::View gameView(sf::Vector2f(m_gameWindowWidth / 2, m_gameWindowHeight / 2), sf::Vector2f(m_gameViewWidth, m_gameViewHeight));
	gameView.zoom(1 / (m_gameWindowWidth / (float)m_gameViewWidth));

	//  Initialization other parameters
	mp_gameTime = new sf::Clock();
	m_elapsedTime = sf::Time::Zero;
	m_idleLag = sf::Time::Zero;
	m_physicsLag = sf::Time::Zero;
	m_msPerIdleFrame = sf::seconds(1.0f / m_FPSCap);
	m_msPerPhysicsFrame = sf::seconds(1.0f / m_physicsFPSCap);
	delete mp_gameWindow;
	mp_gameWindow = new sf::RenderWindow(sf::VideoMode(m_gameWindowWidth, m_gameWindowHeight), m_gameTitle, m_gameWindowMode,
	                                  sf::ContextSettings(0, 0, 1));
	mp_gameWindow->setView(gameView);

	//  Initialization test objects
	m_shape = new sf::CircleShape(50.f);
	m_shape->setFillColor(sf::Color::Green);
	m_shape->setOrigin(m_shape->getRadius(), m_shape->getRadius());
	m_shape->setPosition(mp_gameWindow->getSize().x / 2, mp_gameWindow->getSize().y / 2);
	m_mouseShape = new sf::CircleShape(20.f);
	m_mouseShape->setFillColor(sf::Color::Yellow);
	m_mouseShape->setOrigin(m_mouseShape->getRadius(), m_mouseShape->getRadius());

	return 0;
}

int DronsEngine::Game::handleEvents()
{
	sf::Event event;

	while (mp_gameWindow->pollEvent(event))
	{
		//  Exiting game
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			DronsEngine::GameLogger::log("Exiting...");
			mp_gameWindow->close();
		}

		//  Resizing game window
		if (event.type == sf::Event::Resized)
		{
			DronsEngine::GameLogger::log("Resizing game window...");
			sf::View gameView(sf::Vector2f(m_gameWindowWidth / 2, m_gameWindowHeight / 2),
			                  sf::Vector2f(m_gameViewWidth, m_gameViewHeight));
			gameView.zoom(1 / (mp_gameWindow->getSize().x / (float)m_gameViewWidth));
			mp_gameWindow->setView(gameView);
		}
	}

	return 0;
}

int DronsEngine::Game::physicsUpdate(sf::Time deltaTime)
{
	// Getting mouse position
	sf::Vector2i pixelMousePos = sf::Mouse::getPosition(*mp_gameWindow);
	sf::Vector2f viewMousePos = mp_gameWindow->mapPixelToCoords(pixelMousePos);

	if (DronsEngine::circlesCollide(*m_shape, *m_mouseShape))
	{
		if (DronsEngine::circleAndPointCollide(viewMousePos, *m_shape))
		{
			m_shape->setFillColor(sf::Color::White);
			m_mouseShape->setFillColor(sf::Color::Black);
			DronsEngine::GameLogger::logError("EVENT 1!");
		}
		else
		{
			m_shape->setFillColor(sf::Color::Red);
			m_mouseShape->setFillColor(sf::Color::Magenta);
			DronsEngine::GameLogger::logWarning("EVENT 2!");
		}
	}
	else
	{
		m_shape->setFillColor(sf::Color::Green);
		m_mouseShape->setFillColor(sf::Color::Yellow);
	}

	return 0;
}

int DronsEngine::Game::update(sf::Time deltaTime)
{
	// Getting mouse position
	sf::Vector2i pixelMousePos = sf::Mouse::getPosition(*mp_gameWindow);
	sf::Vector2f viewMousePos = mp_gameWindow->mapPixelToCoords(pixelMousePos);

	m_mouseShape->setPosition(viewMousePos);

	return 0;
}

int DronsEngine::Game::render(sf::Time deltaTime)
{
	mp_gameWindow->clear();

	mp_gameWindow->draw(*m_shape);
	mp_gameWindow->draw(*m_mouseShape);

	mp_gameWindow->display();

	return 0;
}
