#include "Game.h"

DronsEngine::Game::Game(std::string gameTitle) {
	this->gameTitle = gameTitle;
	this->gameWindow = new sf::RenderWindow();
}

int DronsEngine::Game::run() {
	this->init();

	while (this->gameWindow->isOpen()) {
        //  Calculating frametime
		this->elapsedTime = this->gameTime->restart();
		this->idleLag += this->elapsedTime;
		this->physicsLag += this->elapsedTime;

		//  Handling events
		this->handleEvents();

		//  Physics loop
		if (this->physicsLag > this->msPerPhysicsFrame) {
			this->physicsUpdate(this->physicsLag);
			this->physicsLag -= this->msPerPhysicsFrame;
		}

		// Idle and render loop
		if (this->idleLag > this->msPerIdleFrame) {
			this->update(this->idleLag);
			this->render(this->idleLag);
			this->idleLag -= this->msPerIdleFrame;
		}
	}

	return 0;
}

int DronsEngine::Game::init() {
    //  Open settings.ini
	DronsEngine::INIFile INIreader("settings.ini");

    //  Load settings
    std::string readedString = INIreader.read("Video", "Width");
	this->gameWindowWidth = readedString != "" ? std::stoi(readedString) : sf::VideoMode::getDesktopMode().width;
	readedString = INIreader.read("Video", "Height");
	this->gameWindowHeight = readedString != "" ? std::stoi(readedString) : sf::VideoMode::getDesktopMode().height;
	readedString = INIreader.read("Video", "FPSCap");
	this->FPSCap = readedString != "" ? std::stoi(readedString) : 60;
	readedString = INIreader.read("Other", "PhysicsFPSCap");
	this->PhysicsFPSCap = readedString != "" ? std::stoi(readedString) : 30;
	readedString = INIreader.read("Video", "Mode");
	switch (std::stoi(readedString)) {
    case 0:
        this->gameWindowMode = sf::Style::Titlebar | sf::Style::Close;
        break;
    case 1:
        this->gameWindowMode = sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize;
        break;
    case 2:
        this->gameWindowMode = sf::Style::Fullscreen;
        break;
    case 3:
        this->gameWindowMode = sf::Style::None;
        break;
	}
	INIreader.closeINI();

	//  Prepare main view
	sf::View gameView(sf::Vector2f(this->gameWindowWidth / 2, this->gameWindowHeight / 2), sf::Vector2f(this->gameViewWidth, this->gameViewHeight));
	gameView.zoom(1 / (this->gameWindowWidth / (float)this->gameViewWidth));

	//  Initialization other parameters
	this->gameTime = new sf::Clock();
	this->elapsedTime = sf::Time::Zero;
	this->idleLag = sf::Time::Zero;
	this->physicsLag = sf::Time::Zero;
	this->msPerIdleFrame = sf::seconds(1.0f / FPSCap);
	this->msPerPhysicsFrame = sf::seconds(1.0f / PhysicsFPSCap);
	delete this->gameWindow;
	this->gameWindow = new sf::RenderWindow(sf::VideoMode(this->gameWindowWidth, this->gameWindowHeight), this->gameTitle, this->gameWindowMode, sf::ContextSettings(0, 0, 1));
	this->gameWindow->setView(gameView);

	//  Initialization test objects
	this->shape = new sf::CircleShape(50.f);
	this->shape->setFillColor(sf::Color::Green);
	this->shape->setOrigin(this->shape->getRadius(), this->shape->getRadius());
	this->shape->setPosition(this->gameWindow->getSize().x / 2, this->gameWindow->getSize().y / 2);
	this->mouseShape = new sf::CircleShape(20.f);
	this->mouseShape->setFillColor(sf::Color::Yellow);
	this->mouseShape->setOrigin(this->mouseShape->getRadius(), this->mouseShape->getRadius());

	return 0;
}

int DronsEngine::Game::handleEvents() {
	sf::Event event;

	while (this->gameWindow->pollEvent(event)) {
        //  Exiting game
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			this->gameWindow->close();

        // Resizing game window
		if (event.type == sf::Event::Resized) {
			sf::View gameView(sf::Vector2f(this->gameWindowWidth / 2, this->gameWindowHeight / 2), sf::Vector2f(this->gameViewWidth, this->gameViewHeight));
			gameView.zoom(1 / (this->gameWindow->getSize().x / (float)this->gameViewWidth));
			this->gameWindow->setView(gameView);
		}
	}

	return 0;
}

int DronsEngine::Game::physicsUpdate(sf::Time deltaTime) {
    // Getting mouse position
	sf::Vector2i pixelMousePos = sf::Mouse::getPosition(*this->gameWindow);
	sf::Vector2f viewMousePos = this->gameWindow->mapPixelToCoords(pixelMousePos);

	if (DronsEngine::circlesCollide(*this->shape, *this->mouseShape)) {
		if (DronsEngine::circleAndPointCollide(viewMousePos, *this->shape)) {
			this->shape->setFillColor(sf::Color::White);
			this->mouseShape->setFillColor(sf::Color::Black);
		} else {
			this->shape->setFillColor(sf::Color::Red);
			this->mouseShape->setFillColor(sf::Color::Magenta);

		}
	} else {
		this->shape->setFillColor(sf::Color::Green);
		this->mouseShape->setFillColor(sf::Color::Yellow);
	}

	return 0;
}

int DronsEngine::Game::update(sf::Time deltaTime) {
    // Getting mouse position
	sf::Vector2i pixelMousePos = sf::Mouse::getPosition(*this->gameWindow);
	sf::Vector2f viewMousePos = this->gameWindow->mapPixelToCoords(pixelMousePos);

	this->mouseShape->setPosition(viewMousePos);

	return 0;
}

int DronsEngine::Game::render(sf::Time deltaTime) {
	this->gameWindow->clear();

	this->gameWindow->draw(*this->shape);
	this->gameWindow->draw(*this->mouseShape);

	this->gameWindow->display();

	return 0;
}
