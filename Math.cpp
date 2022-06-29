#include "Math.h"

float DronsEngine::distance(float x0, float y0, float x1, float y1){
    float dx = x1 - x0;
    float dy = y1 - y0;
    return std::sqrt(dx * dx + dy * dy);
}

int DronsEngine::circlesCollide(sf::CircleShape shape1, sf::CircleShape shape2){
    if (distance(shape1.getPosition().x, shape1.getPosition().y, shape2.getPosition().x, shape2.getPosition().y)
        < (shape1.getRadius() + shape2.getRadius())){
        return 1;
    }
    return 0;
}

int DronsEngine::circleAndPointCollide(sf::Vector2f point0, sf::CircleShape shape0){
    if (distance(point0.x, point0.y, shape0.getPosition().x, shape0.getPosition().y) < shape0.getRadius()){
        return 1;
    }
    return 0;
}

float DronsEngine::lerp(float a, float b, float t){
    return a * (1 - t) + b * t;
}
