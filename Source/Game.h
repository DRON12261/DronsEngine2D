#ifndef GAME_H
#define GAME_H

//{Includes}
#include <States/MainMenuState.h>
//}

class Game
{
private:
    //{Variables}
    sf::RenderWindow *window;
    sf::Event sfEvent;
    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSettings;
    bool fullscreen;

    sf::Clock dtClock;
    float dt;

    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;
    //}

    //{Initialization}
    void initVariables();
    void initWindow();
    void initKeys();
    void initStates();
    //}
public:
    //{Constructor and Destructor}
    Game();
    virtual ~Game();
    //}

    //{Functions}
    //{Regular}
    void endApplication();
    //}

    //{Update}
    void updateDt();
    void updateSFMLEvents();
    void update();
    //}

    //{Render}
    void render();
    //}

    //{Core}
    void run();
    //}
    //}
};

#endif
