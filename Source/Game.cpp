#include "Game.h"

DronsEngine::Game::Game(std::string gameTitle) {
	this->gameTitle = gameTitle;
	gameWindow = new sf::RenderWindow();
}

int DronsEngine::Game::run() {
	init();

	while (gameWindow->isOpen()) {
        //  Calculating frametime
		elapsedTime = gameTime->restart();
		idleLag += elapsedTime;
		physicsLag += elapsedTime;

		//  Handling events
		handleEvents();

		//  Physics loop
		if (physicsLag > msPerPhysicsFrame) {
			physicsUpdate(physicsLag);
			physicsLag -= msPerPhysicsFrame;
		}

		// Idle and render loop
		if (idleLag > msPerIdleFrame) {
			update(idleLag);
			render(idleLag);
			idleLag -= msPerIdleFrame;
		}
	}

	return 0;
}

int DronsEngine::Game::init() {
    //  Open settings.ini
	DronsEngine::INIFile INIreader("settings.ini");

    //  Load settings
    std::string readedString = INIreader.read("Video", "Width");
	gameWindowWidth = readedString != "" ? std::stoi(readedString) : sf::VideoMode::getDesktopMode().width;
	readedString = INIreader.read("Video", "Height");
	gameWindowHeight = readedString != "" ? std::stoi(readedString) : sf::VideoMode::getDesktopMode().height;
	readedString = INIreader.read("Video", "FPSCap");
	FPSCap = readedString != "" ? std::stoi(readedString) : 60;
	readedString = INIreader.read("Other", "PhysicsFPSCap");
	PhysicsFPSCap = readedString != "" ? std::stoi(readedString) : 30;
	readedString = INIreader.read("Video", "Mode");
	switch (std::stoi(readedString)) {
    case 0:
        gameWindowMode = sf::Style::Titlebar | sf::Style::Close;
        break;
    case 1:
        gameWindowMode = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;
        break;
    case 2:
        gameWindowMode = sf::Style::Fullscreen;
        break;
    case 3:
        gameWindowMode = sf::Style::None;
        break;
	}
	INIreader.closeINI();

	//  Prepare main view
	sf::View gameView(sf::Vector2f(gameWindowWidth / 2, gameWindowHeight / 2), sf::Vector2f(gameViewWidth, gameViewHeight));
	gameView.zoom(1 / (gameWindowWidth / (float)gameViewWidth));

	//  Initialization other parameters
	gameTime = new sf::Clock();
	elapsedTime = sf::Time::Zero;
	idleLag = sf::Time::Zero;
	physicsLag = sf::Time::Zero;
	msPerIdleFrame = sf::seconds(1.0f / FPSCap);
	msPerPhysicsFrame = sf::seconds(1.0f / PhysicsFPSCap);
	delete gameWindow;
	gameWindow = new sf::RenderWindow(sf::VideoMode(gameWindowWidth, gameWindowHeight), gameTitle, gameWindowMode, sf::ContextSettings(0, 0, 1));
	gameWindow->setView(gameView);

	//  Initialization test objects
	shape = new sf::CircleShape(50.f);
	shape->setFillColor(sf::Color::Green);
	shape->setOrigin(shape->getRadius(), shape->getRadius());
	shape->setPosition(gameWindow->getSize().x / 2, gameWindow->getSize().y / 2);
	mouseShape = new sf::CircleShape(20.f);
	mouseShape->setFillColor(sf::Color::Yellow);
	mouseShape->setOrigin(mouseShape->getRadius(), mouseShape->getRadius());

	return 0;
}

int DronsEngine::Game::handleEvents() {
	sf::Event event;

	while (gameWindow->pollEvent(event)) {
        //  Exiting game
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			gameWindow->close();

        // Resizing game window
		if (event.type == sf::Event::Resized) {
			sf::View gameView(sf::Vector2f(gameWindowWidth / 2, gameWindowHeight / 2), sf::Vector2f(gameViewWidth, gameViewHeight));
			gameView.zoom(1 / (gameWindow->getSize().x / (float)gameViewWidth));
			gameWindow->setView(gameView);
		}
	}

	return 0;
}

int DronsEngine::Game::physicsUpdate(sf::Time deltaTime) {
    // Getting mouse position
	sf::Vector2i pixelMousePos = sf::Mouse::getPosition(*gameWindow);
	sf::Vector2f viewMousePos = gameWindow->mapPixelToCoords(pixelMousePos);

	if (DronsEngine::circlesCollide(*shape, *mouseShape)) {
		if (DronsEngine::circleAndPointCollide(viewMousePos, *shape)) {
			shape->setFillColor(sf::Color::White);
			mouseShape->setFillColor(sf::Color::Black);
		} else {
			shape->setFillColor(sf::Color::Red);
			mouseShape->setFillColor(sf::Color::Magenta);

		}
	} else {
		shape->setFillColor(sf::Color::Green);
		mouseShape->setFillColor(sf::Color::Yellow);
	}

	return 0;
}

int DronsEngine::Game::update(sf::Time deltaTime) {
    // Getting mouse position
	sf::Vector2i pixelMousePos = sf::Mouse::getPosition(*gameWindow);
	sf::Vector2f viewMousePos = gameWindow->mapPixelToCoords(pixelMousePos);

	mouseShape->setPosition(viewMousePos);

	return 0;
}

int DronsEngine::Game::render(sf::Time deltaTime) {
	gameWindow->clear();

	gameWindow->draw(*shape);
	gameWindow->draw(*mouseShape);

	gameWindow->display();

	return 0;
}
