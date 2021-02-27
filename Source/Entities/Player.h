#ifndef PLAYER_H
#define PLAYER_H

//{Includes}
#include <Entities/Entity.h>
//}

class Player : public Entity
{
private:
    //{Variables}

    //}

    //{Initialization}
    void initVariables();
    void initComponents();
    //}
public:
    //{Constructor and Destructor}
    Player(float x, float y, sf::Texture& texture);
    virtual ~Player();
    //}

    //{Functions}

    //}
};

#endif
