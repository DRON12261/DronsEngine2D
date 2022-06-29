#include "Game.h"

DronsEngine::Game::Game(std::string gameTitle, int gameWindowWidth, int gameWindowHeight){
    this->gameTitle = gameTitle;
    this->gameWindowWidth = gameWindowWidth;
    this->gameWindowHeight = gameWindowHeight;
    this->gameWindow = new sf::RenderWindow(sf::VideoMode(this->gameWindowWidth, this->gameWindowHeight), this->gameTitle);
}

int DronsEngine::Game::run(){
    this->init();
    this->gameWindow->setFramerateLimit(this->FPSCap);

    while (this->gameWindow->isOpen())
    {
        this->elapsedTime = this->gameTime->restart();
        this->idleLag += this->elapsedTime;
        this->physicsLag += this->elapsedTime;

        this->handleEvents();

        if (this->physicsLag > this->msPerPhysicsFrame)
        {
            this->physicsUpdate();
            this->physicsLag -= this->msPerPhysicsFrame;
        }

        if (this->idleLag > this->msPerIdleFrame)
        {
            this->update();
            this->idleLag -= this->msPerIdleFrame;
        }

        this->render();
    }

    return 0;
}

int DronsEngine::Game::init(){
    this->shape = new sf::CircleShape(50.f);
    this->shape->setFillColor(sf::Color::Green);
    this->shape->setOrigin(this->shape->getRadius(), this->shape->getRadius());
    this->shape->setPosition(this->gameWindow->getSize().x/2, this->gameWindow->getSize().y/2);
    this->mouseShape = new sf::CircleShape(20.f);
    this->mouseShape->setFillColor(sf::Color::Yellow);
    this->mouseShape->setOrigin(this->mouseShape->getRadius(), this->mouseShape->getRadius());

    this->gameTime = new sf::Clock();
    this->elapsedTime = sf::Time::Zero;
    this->idleLag = sf::Time::Zero;
    this->physicsLag = sf::Time::Zero;
    this->FPSCap = 60;
    this->PhysicsFPSCap = 30;
    this->msPerIdleFrame = sf::seconds(1.0f/FPSCap);
    this->msPerPhysicsFrame = sf::seconds(1.0f/PhysicsFPSCap);
    this->gameWindow = new sf::RenderWindow(sf::VideoMode(this->gameWindowWidth, this->gameWindowHeight), this->gameTitle, sf::Style::Fullscreen, sf::ContextSettings(0,0,1));
    //this->gameWindow->setVerticalSyncEnabled(true);
}

int DronsEngine::Game::handleEvents(){
    sf::Event event;
    while (this->gameWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            this->gameWindow->close();
    }

    return 0;
}

int DronsEngine::Game::physicsUpdate(){
    if (DronsEngine::circlesCollide(*this->shape, *this->mouseShape)){
        if (DronsEngine::circleAndPointCollide((sf::Vector2f)sf::Mouse::getPosition(*this->gameWindow), *this->shape))
        {
            this->shape->setFillColor(sf::Color::White);
            this->mouseShape->setFillColor(sf::Color::Black);
        }
        else{
            this->shape->setFillColor(sf::Color::Red);
            this->mouseShape->setFillColor(sf::Color::Magenta);

        }
    }
    else{
        this->shape->setFillColor(sf::Color::Green);
        this->mouseShape->setFillColor(sf::Color::Yellow);
    }

    return 0;
}

int DronsEngine::Game::update(){
    this->mouseShape->setPosition((sf::Vector2f)sf::Mouse::getPosition(*this->gameWindow));

    return 0;
}

int DronsEngine::Game::render(){
    this->gameWindow->clear();
    this->gameWindow->draw(*this->shape);
    this->gameWindow->draw(*this->mouseShape);
    this->gameWindow->display();

    return 0;
}
