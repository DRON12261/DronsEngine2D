#include "Game.h"

DronsEngine::Game::Game(std::string t_gameTitle)
{
	GameLogger::log("Launching \"" + t_gameTitle + "\"...", Logger::Type::INFO, "Game");
	this->m_gameTitle = t_gameTitle;
	mp_gameWindow = new sf::RenderWindow();

	init();
}

DronsEngine::Game::~Game()
{
	delete mp_gameWindow;
	delete mp_gameTime;

	while (!m_gameStates.empty())
	{
		m_gameStates.top()->endState();
		delete m_gameStates.top();
		m_gameStates.pop();
	}
}

int DronsEngine::Game::run()
{
	GameLogger::log("Start game loop...", Logger::Type::INFO, "Game Loop");
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

		//	Check game states
		if (!m_gameStates.empty())
		{
			if (m_gameStates.top()->isQuit())
			{
				m_gameStates.top()->endState();
				delete m_gameStates.top();
				m_gameStates.pop();
			}
		}
		else
		{
			close();
		}
	}

	return 0;
}

int DronsEngine::Game::init()
{
	GameLogger::log("Initialization...", Logger::Type::INFO, "Game");

	initSettings();
	initWindow();
	initStates();
	initObjects();

	return 0;
}

int DronsEngine::Game::initSettings()
{
	//  Open settings.ini
	INIFile INIreader("Configs/Settings.ini");

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

	//	Initialization other parameters
	mp_gameTime = new sf::Clock();
	m_elapsedTime = sf::Time::Zero;
	m_idleLag = sf::Time::Zero;
	m_physicsLag = sf::Time::Zero;
	m_msPerIdleFrame = sf::seconds(1.0f / m_FPSCap);
	m_msPerPhysicsFrame = sf::seconds(1.0f / m_physicsFPSCap);

	return 0;
}

int DronsEngine::Game::initWindow()
{
	//  Prepare main view
	sf::View gameView(sf::Vector2f(m_gameWindowWidth / 2, m_gameWindowHeight / 2),
	                  sf::Vector2f(m_gameViewWidth, m_gameViewHeight));
	gameView.zoom(1 / (m_gameWindowWidth / (float)m_gameViewWidth));

	//  Initialization window
	delete mp_gameWindow;
	mp_gameWindow = new sf::RenderWindow(sf::VideoMode(m_gameWindowWidth, m_gameWindowHeight), m_gameTitle, m_gameWindowMode,
	                                     sf::ContextSettings(0, 0, 1));
	mp_gameWindow->setView(gameView);

	return 0;
}

int DronsEngine::Game::initStates()
{
	m_gameStates.push(new SceneState(mp_gameWindow));
	m_gameStates.top()->startState();

	return 0;
}

int DronsEngine::Game::initObjects()
{
	return 0;
}

int DronsEngine::Game::handleEvents()
{
	sf::Event event;

	while (mp_gameWindow->pollEvent(event))
	{
		//  Exiting game
		if (event.type == sf::Event::Closed)
		{
			close();
		}

		//  Resizing game window
		if (event.type == sf::Event::Resized)
		{
			GameLogger::log("Resizing game window...", Logger::Type::DEBUG, "Game Loop");
			sf::View gameView(sf::Vector2f(m_gameWindowWidth / 2, m_gameWindowHeight / 2),
			                  sf::Vector2f(m_gameViewWidth, m_gameViewHeight));
			gameView.zoom(1 / (mp_gameWindow->getSize().x / (float)m_gameViewWidth));
			mp_gameWindow->setView(gameView);
		}

		if (!m_gameStates.empty())
			m_gameStates.top()->handleEvents(event);
	}

	return 0;
}

int DronsEngine::Game::physicsUpdate(const sf::Time& t_deltaTime)
{
	if (!m_gameStates.empty())
		m_gameStates.top()->physicsUpdate(t_deltaTime);

	return 0;
}

int DronsEngine::Game::update(const sf::Time& t_deltaTime)
{
	if (!m_gameStates.empty())
		m_gameStates.top()->update(t_deltaTime);

	return 0;
}

int DronsEngine::Game::render(const sf::Time& t_deltaTime)
{
	mp_gameWindow->clear();

	if (!m_gameStates.empty())
		m_gameStates.top()->render(t_deltaTime);

	mp_gameWindow->display();

	return 0;
}

int DronsEngine::Game::close()
{
	GameLogger::log("Exiting...", Logger::Type::INFO, "Game Loop");
	mp_gameWindow->close();

	return 0;
}
