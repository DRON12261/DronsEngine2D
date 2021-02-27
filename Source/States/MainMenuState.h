#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

//{Includes}
#include <States/GameState.h>
#include <UI/Button.h>
//}

class MainMenuState : public State
{
private:
    //{Variables}
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    FPSCounter* fpsCounter;

    std::map<std::string, Button*> buttons;
    //}

    //{Initializtion}
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
    //}
public:
    //{Constructor and Destrictor}
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();
    //}

    //{Functions}
    void updateKeybinds(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget* target = nullptr);
    void render(sf::RenderTarget* target = nullptr);
    //}
};

#endif
