#ifndef STATE_H
#define STATE_H

//{Includes}
#include <Entities/Player.h>
//}

class State
{
private:

protected:
    //{Variables}
    std::stack<State*>* states;
    sf::RenderWindow* window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    //}

    //{Resources}
    std::map<std::string, sf::Texture> textures;
    //}

    //{Functions (protected)}
    virtual void initKeybinds() = 0;
    //}
public:
    //{Constructor and Destructor}
    State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~State();
    //}

    //{Accessors}
    const bool& getQuit() const;
    //}

    //{Functions}
    void endState();
    virtual void updateMousePositions();
    virtual void updateKeybinds(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget* target = nullptr) = 0;
    //}
};

#endif
