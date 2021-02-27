#include "Entity.h"

//{Initialization}
void Entity::initVariables()
{
    this->movementComponent = NULL;
}
//}

//{Constructor and Destructor}
Entity::Entity()
{
    this->initVariables();
}

Entity::~Entity()
{
    delete this->movementComponent;
}
//}

//{Component functions}
void Entity::setTexture(sf::Texture& texture)
{
    this->sprite.setTexture(texture);
    this->sprite.setScale(2.f, 2.f);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}
//}

//{Functions}
void Entity::setPosition(const float x, const float y)
{
    this->sprite.setPosition(x, y);
}

void Entity::move(const float dirX, const float dirY, const float& dt)
{
    if (this->movementComponent)
    {
        this->movementComponent->move(dirX, dirY, dt);
    }
}

void Entity::update(const float& dt)
{
    if (this->movementComponent)
    {
        this->movementComponent->update(dt);
    }
}

void Entity::render(sf::RenderTarget* target)
{
    target->draw(this->sprite);
}
//}
