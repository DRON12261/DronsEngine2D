#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <cmath>

namespace DronsEngine {
	float distance(float x0, float y0, float x1, float y1);
	int circlesCollide(sf::CircleShape shape1, sf::CircleShape shape2);
	int circleAndPointCollide(sf::Vector2f point0, sf::CircleShape shape0);
	float lerp(float a, float b, float t);
}  // namespace DronsEngine

