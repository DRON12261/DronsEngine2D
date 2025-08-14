#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <string>
#include <cmath>

namespace DronsEngine
{
	float distance(float t_x0, float t_y0, float t_x1, float t_y1);
	int isCirclesCollide(sf::CircleShape t_shape1, sf::CircleShape t_shape2);
	int isCircleAndPointCollide(sf::Vector2f t_point0, sf::CircleShape t_shape0);
	int isCircleAndPointCollide(sf::Vector2f t_point0, sf::Vector2f t_shape0_position, float t_shape0_radius);
	float lerp(float t_a, float t_b, float t_t);
}  // namespace DronsEngine
