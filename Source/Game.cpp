#include "Game.h"

DronsEngine::Game::Game(std::string t_gameTitle)
{
	GameLogger::log("Launching \"" + t_gameTitle + "\"...", Logger::Type::LOG_INFO, "Core");
	this->m_gameTitle = t_gameTitle;
	mp_gameWindow = new sf::RenderWindow();

	init();

	GameLogger::log("Initialization complete", Logger::Type::LOG_INFO, "Core");
}

DronsEngine::Game::~Game()
{
	GameLogger::log("Memory cleaning...", Logger::Type::LOG_INFO, "Core");

	delete mp_gameWindow;
	delete mp_gameTime;

	while (!m_gameStates.empty())
	{
		m_gameStates.top()->endState();
		delete m_gameStates.top();
		m_gameStates.pop();
	}

	GameLogger::log("Memory cleared", Logger::Type::LOG_INFO, "Core");
}

void DronsEngine::Game::run()
{
	GameLogger::log("Start game loop...", Logger::Type::LOG_INFO, "Game");
	while (mp_gameWindow->isOpen())
	{
		// Calculating frametime
		m_elapsedTime = mp_gameTime->restart();
		m_idleLag += m_elapsedTime;
		m_physicsLag += m_elapsedTime;

		// Handling events
		handleEvents();

		// Physics loop
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

		// Check game states
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
}

void DronsEngine::Game::init()
{
	GameLogger::log("Initialization...", Logger::Type::LOG_INFO, "Core");

	initSettings();
	initWindow();
	initNetwork();
	initStates();
	initObjects();
}

void DronsEngine::Game::initSettings()
{
	GameLogger::log("Initializing settings...", Logger::Type::LOG_INFO, "Core");

	// Open settings.ini
	INIFile INIConfig("Configs/Settings.ini");

	// Load settings
	std::string readedString = INIConfig.read("Video", "Width");
	if (readedString != "")
	{
		m_gameWindowWidth = std::stoi(readedString);
	}
	else
	{
		m_gameWindowWidth = sf::VideoMode::getDesktopMode().width;
		INIConfig.write("Video", "Width", std::to_string(m_gameWindowWidth));
	}

	readedString = INIConfig.read("Video", "Height");
	if (readedString != "")
	{
		m_gameWindowHeight = std::stoi(readedString);
	}
	else
	{
		m_gameWindowHeight = sf::VideoMode::getDesktopMode().height;
		INIConfig.write("Video", "Height", std::to_string(m_gameWindowHeight));
	}

	readedString = INIConfig.read("Video", "FPSCap");
	if (readedString != "")
	{
		m_FPSCap = std::stoi(readedString);
	}
	else
	{
		m_FPSCap = 60;
		INIConfig.write("Video", "FPSCap", std::to_string(m_FPSCap));
	}

	readedString = INIConfig.read("Other", "PhysicsFPSCap");
	if (readedString != "")
	{
		m_physicsFPSCap = std::stoi(readedString);
	}
	else
	{
		m_physicsFPSCap = 30;
		INIConfig.write("Other", "PhysicsFPSCap", std::to_string(m_physicsFPSCap));
	}

	readedString = INIConfig.read("Video", "Style");
	if (readedString != "")
	{
		m_gameWindowStyle = std::stoi(readedString);
	}
	else
	{
		m_gameWindowStyle = sf::Style::Default;
		INIConfig.write("Video", "Style", std::to_string(m_gameWindowStyle));
	}

	INIConfig.saveINI();
	INIConfig.closeINI();

	// Initialization other parameters
	mp_gameTime = new sf::Clock();
	m_elapsedTime = sf::Time::Zero;
	m_idleLag = sf::Time::Zero;
	m_physicsLag = sf::Time::Zero;
	m_msPerIdleFrame = sf::seconds(1.0f / m_FPSCap);
	m_msPerPhysicsFrame = sf::seconds(1.0f / m_physicsFPSCap);

	GameLogger::log("Settings initialized", Logger::Type::LOG_INFO, "Core");
}

void DronsEngine::Game::initWindow()
{
	GameLogger::log("Initializing window...", Logger::Type::LOG_INFO, "Core");

	// Prepare main view
	sf::View gameView(sf::Vector2f(m_gameWindowWidth / 2, m_gameWindowHeight / 2),
	                  sf::Vector2f(m_gameViewWidth, m_gameViewHeight));
	gameView.zoom(1 / (m_gameWindowWidth / (float)m_gameViewWidth));

	// Initialization window
	delete mp_gameWindow;
	mp_gameWindow = new sf::RenderWindow(sf::VideoMode(m_gameWindowWidth, m_gameWindowHeight), m_gameTitle,
	                                     m_gameWindowStyle, sf::ContextSettings(0, 0, 1));
	mp_gameWindow->setView(gameView);

	GameLogger::log("Window initialized", Logger::Type::LOG_INFO, "Core");
}

void DronsEngine::Game::initNetwork()
{
	GameLogger::log("Initializing network...", Logger::Type::LOG_INFO, "Network");

	// Initialization ENet
	if (enet_initialize() != 0)
	{
		GameLogger::log("ENet initialization failed!", Logger::Type::LOG_FATAL, "Network");
		exit(EXIT_FAILURE);
	}

	GameLogger::log("Network initialized", Logger::Type::LOG_INFO, "Network");
}

void DronsEngine::Game::initStates()
{
	GameLogger::log("Initializing game states...", Logger::Type::LOG_INFO, "Core");

	m_gameStates.push(new SceneState(mp_gameWindow));
	m_gameStates.top()->startState();

	GameLogger::log("Game states initialized", Logger::Type::LOG_INFO, "Core");
}

void DronsEngine::Game::initObjects() {}

void DronsEngine::Game::handleEvents()
{
	sf::Event event;

	while (mp_gameWindow->pollEvent(event))
	{
		// Exiting game
		if (event.type == sf::Event::Closed)
		{
			close();
		}

		// Resizing game window
		if (event.type == sf::Event::Resized)
		{
			GameLogger::log("Resizing game window...", Logger::Type::LOG_DEBUG, "Game");
			sf::View gameView(sf::Vector2f(m_gameWindowWidth / 2, m_gameWindowHeight / 2),
			                  sf::Vector2f(m_gameViewWidth, m_gameViewHeight));
			gameView.zoom(1 / (mp_gameWindow->getSize().x / (float)m_gameViewWidth));
			mp_gameWindow->setView(gameView);
		}

		if (!m_gameStates.empty())
			m_gameStates.top()->handleEvents(event);
	}
}

void DronsEngine::Game::physicsUpdate(const sf::Time& t_deltaTime)
{
	if (!m_gameStates.empty())
		m_gameStates.top()->physicsUpdate(t_deltaTime);
}

void DronsEngine::Game::update(const sf::Time& t_deltaTime)
{
	if (!m_gameStates.empty())
		m_gameStates.top()->update(t_deltaTime);
}

void DronsEngine::Game::render(const sf::Time& t_deltaTime)
{
	mp_gameWindow->clear();

	if (!m_gameStates.empty())
		m_gameStates.top()->render(t_deltaTime);

	mp_gameWindow->display();
}

void DronsEngine::Game::close()
{
	GameLogger::log("Exiting...", Logger::Type::LOG_INFO, "Game");

	mp_gameWindow->close();

	enet_deinitialize();
}