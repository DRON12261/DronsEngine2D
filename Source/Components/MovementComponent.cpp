#include "MovementComponent.h"

//{Constructor and Destructor}
MovementComponent::MovementComponent(sf::Sprite& sprite,
    float maxVelocity, float acceleration, float deceleration)
    : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{

}
//}

//{Accessors}
const sf::Vector2f& MovementComponent::getVelocity() const
{
    return this->velocity;
}
//}

//{Functions}
void MovementComponent::move(const float dirX, const float dirY, const float& dt)
{
    //Acceleration
    this->velocity.x += this->acceleration * dirX * dt;
    this->velocity.y += this->acceleration * dirY * dt;
}

void MovementComponent::update(const float& dt)
{
    //Deceleration
    if (this->velocity.x > 0.f)
    {
        if (this->velocity.x > this->maxVelocity)
            this->velocity.x = this->maxVelocity;

        this->velocity.x -= deceleration * dt;
        if (this->velocity.x < 0.f)
            this->velocity.x = 0.f;
    }
    else if (this->velocity.x < 0.f)
    {
        if (this->velocity.x < -this->maxVelocity)
            this->velocity.x = -this->maxVelocity;

        this->velocity.x += deceleration * dt;
        if (this->velocity.x > 0.f)
            this->velocity.x = 0.f;
    }

    if (this->velocity.y > 0.f)
    {
        if (this->velocity.y > this->maxVelocity)
            this->velocity.y = this->maxVelocity;

        this->velocity.y -= deceleration * dt;
        if (this->velocity.y < 0.f)
            this->velocity.y = 0.f;
    }
    else if (this->velocity.y < 0.f)
    {
        if (this->velocity.y < -this->maxVelocity)
            this->velocity.y = -this->maxVelocity;

        this->velocity.y += deceleration * dt;
        if (this->velocity.y > 0.f)
            this->velocity.y = 0.f;
    }

    //Final move
    this->sprite.move(this->velocity * dt);
}
//}
