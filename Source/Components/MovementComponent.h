#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

//{Includes}
#include <UI/FPSCounter.h>
//}

class MovementComponent
{
private:
    //{Variables}
    sf::Sprite& sprite;

    float maxVelocity;
    float acceleration;
    float deceleration;

    sf::Vector2f velocity;
    //}

    //{Initialization}

    //}

public:
    //{Constructor and Destructor}
    MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();
    //}

    //{Accessors}
    const sf::Vector2f& getVelocity() const;
    //}

    //{Functions}
    void move(const float dirX, const float dirY, const float& dt);
    void update(const float& dt);
    //}
};

#endif
