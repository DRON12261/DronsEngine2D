#include "Game.h"

//Static functions

//{Initialization}
void Game::initVariables()
{
    this->window = NULL;
    this->fullscreen = false;

    this->dt = 0.f;
}

void Game::initWindow()
{
    std::ifstream ifs("Config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "None";
    sf::VideoMode windowBounds = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    unsigned framerateLimit = 120;
    bool vertSyncEnabled = false;
    unsigned antialiasingLevel = 0;

    if (ifs.is_open())
    {
        std::getline(ifs, title);
        ifs >> windowBounds.width >> windowBounds.height;
        ifs >> this->fullscreen;
        ifs >> framerateLimit;
        ifs >> vertSyncEnabled;
        ifs >> antialiasingLevel;
    }

    ifs.close();

    this->windowSettings.antialiasingLevel = antialiasingLevel;
    if (fullscreen)
        this->window = new sf::RenderWindow(windowBounds, title, sf::Style::Fullscreen, windowSettings);
    else
        this->window = new sf::RenderWindow(windowBounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
    this->window->setFramerateLimit(framerateLimit);
    this->window->setVerticalSyncEnabled(vertSyncEnabled);
}

void Game::initKeys()
{
    std::ifstream ifs("Config/supportedKeys.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        int keyValue = 0;

        while(ifs >> key >> keyValue)
        {
            this->supportedKeys[key] = keyValue;
        }
    }

    ifs.close();

    //DEBUG
    for (auto i : this->supportedKeys)
    {
        std::cout << i.first << " " << i.second << "\n";
    }
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
}
//}

//{Constructor and Destructor}

Game::Game()
{
    this->initWindow();
    this->initKeys();
    this->initStates();
}

Game::~Game()
{
    delete this->window;

    while(!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }
}
//}
//{Functions}
//{Regular}
void Game::endApplication()
{
    std::cout << "Ending Application!\n";
}
//}

//{Update}
void Game::updateDt()
{
    this->dt = this->dtClock.restart().asSeconds();

    //system("cls");
    //std::cout << this->dt << "\n";
}

void Game::updateSFMLEvents()
{
    while(this->window->pollEvent(this->sfEvent))
    {
        if(this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    //Application end
    else
    {
        this->endApplication();
        this->window->close();
    }
}
//}

//{Render}
void Game::render()
{
    this->window->clear();

    //Render things
    if (!this->states.empty())
    {
        this->states.top()->render(this->window);
    }

    this->window->display();
}
//}

//{Core}
void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}
//}
//}
//}
