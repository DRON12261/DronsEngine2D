#include "GameState.h"

//{Initializtion}
void GameState::initKeybinds()
{
    std::ifstream ifs("Config/gameStateKeybinds.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string keyValue = "";

        while(ifs >> key >> keyValue)
        {
            this->keybinds[key] = this->supportedKeys->at(keyValue);
        }
    }

    ifs.close();
}

void GameState::initTextures()
{
    if (!this->textures["PLAYER_IDLE"].loadFromFile("Sprites/Char.png", sf::IntRect(0, 0, 32, 32)))
    {
        throw("ERROR::GAMESTATE::COULD NOT LOAD PLAYER_IDLE TEXTURE");
    }
    this->textures["PLAYER_IDLE"].setSmooth(false);
}

void GameState::initPlayers()
{
    this->player = new Player(0, 0, this->textures["PLAYER_IDLE"]);
}
//}

//{Constructor and Destructor}
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
    this->initKeybinds();
    this->initTextures();
    this->initPlayers();
}

GameState::~GameState()
{
    delete this->player;
}
//}

//{Functions}
void GameState::updateKeybinds(const float& dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
    {
        this->player->move(-1.f, 0.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
    {
        this->player->move(1.f, 0.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
    {
        this->player->move(0.f, -1.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
    {
        this->player->move(0.f, 1.f, dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
    {
        this->endState();
    }
}

void GameState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateKeybinds(dt);

    this->player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->window;
    }

    this->player->render(target);
}
//}
