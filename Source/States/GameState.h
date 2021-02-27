#ifndef GAMESTATE_H
#define GAMESTATE_H

//{Includes}
#include <States/State.h>
//}

class GameState : public State
{
private:
    //{Variables}
    Player* player;
    //}

    //{Initializtion}
    void initKeybinds();
    void initTextures();
    void initPlayers();
    //}
public:
    //{Constructor and Destructor}
    GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();
    //}

    //{Functions}
    void updateKeybinds(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
    //}
};

#endif
