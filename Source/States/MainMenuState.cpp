#include "MainMenuState.h"

//{Initialization}
void MainMenuState::initVariables()
{
    this->fpsCounter = NULL;
}

void MainMenuState::initBackground()
{
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
    if (!this->backgroundTexture.loadFromFile("Sprites/MainMenuBackground.png"))
    {
        throw("ERROR::MAINMENUSTATE::FAILED TO LOAD BACKGROUND TEXTURE");
    }
    this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts()
{
    if(!this->font.loadFromFile("Fonts/MainMenuFont3.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void MainMenuState::initKeybinds()
{
    std::ifstream ifs("Config/mainMenuStateKeybinds.ini");

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

void MainMenuState::initButtons()
{
    this->buttons["GAME_STATE"] = new Button(50, 640, 150, 50, &this->font, "New Game", 28,
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 20), sf::Color(150, 150, 150, 20), sf::Color(20, 20, 20, 20));

    this->buttons["SETTINGS"] = new Button(250, 640, 150, 50, &this->font, "Settings", 28,
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 20), sf::Color(150, 150, 150, 20), sf::Color(20, 20, 20, 20));

    this->buttons["EDITOR_STATE"] = new Button(450, 640, 150, 50, &this->font, "Editor", 28,
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 20), sf::Color(150, 150, 150, 20), sf::Color(20, 20, 20, 20));

    this->buttons["EXIT"] = new Button(1080, 640, 150, 50, &this->font, "Exit Game", 28,
        sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
        sf::Color(70, 70, 70, 20), sf::Color(150, 150, 150, 20), sf::Color(20, 20, 20, 20));
}
//}

//{Constructor and Destructor}
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(window, supportedKeys, states)
{
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();

    this->fpsCounter = new FPSCounter(this->font);
}

MainMenuState::~MainMenuState()
{
    for (auto i = this->buttons.begin(); i != this->buttons.end(); ++i)
    {
        delete i->second;
    }
}
//}

//{Functions}
void MainMenuState::updateKeybinds(const float& dt)
{

}

void MainMenuState::updateButtons()
{
    for (auto &i : this->buttons)
    {
        i.second->update(this->mousePosView);
    }

    if (this->buttons["GAME_STATE"]->isPressed())
    {
        this->states->push(new GameState(this->window, this->supportedKeys, this->states));
    }

    if (this->buttons["EXIT"]->isPressed())
    {
        this->endState();
    }
}

void MainMenuState::update(const float& dt)
{
    this->updateMousePositions();
    this->updateKeybinds(dt);
    this->updateButtons();

    this->fpsCounter->update();
}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
    for (auto &i : this->buttons)
    {
        i.second->render(target);
    }
}

void MainMenuState::render(sf::RenderTarget* target)
{
    if (!target)
    {
        target = this->window;
    }

    target->draw(this->background);

    this->renderButtons(target);
    this->fpsCounter->render(target);

//    sf::Text mouseText;
//    mouseText.setPosition(mousePosView.x, mousePosView.y + 10);
//    mouseText.setFont(this->font);
//    mouseText.setCharacterSize(24);
//    std::stringstream ss;
//    ss << this->mousePosView.x << " " << this->mousePosView.y;
//    mouseText.setString(ss.str());
//    target->draw(mouseText);
}
//}
