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
	float distance(float t_x0, float t_y0, float t_x1, float t_y1);
	int circlesCollide(sf::CircleShape t_shape1, sf::CircleShape t_shape2);
	int circleAndPointCollide(sf::Vector2f t_point0, sf::CircleShape t_shape0);
	float lerp(float t_a, float t_b, float t_t);
}  // namespace DronsEngine
