#include "Math.h"

float DronsEngine::distance(float t_x0, float t_y0, float t_x1, float t_y1)
{
	float dx = t_x1 - t_x0;
	float dy = t_y1 - t_y0;
	return std::sqrt(dx * dx + dy * dy);
}

int DronsEngine::isCirclesCollide(sf::CircleShape t_shape1, sf::CircleShape t_shape2)
{
	if (distance(t_shape1.getPosition().x, t_shape1.getPosition().y, t_shape2.getPosition().x, t_shape2.getPosition().y) <
	    (t_shape1.getRadius() + t_shape2.getRadius()))
	{
		return 1;
	}

	return 0;
}

int DronsEngine::isCircleAndPointCollide(sf::Vector2f t_point0, sf::CircleShape t_shape0)
{
	if (distance(t_point0.x, t_point0.y, t_shape0.getPosition().x, t_shape0.getPosition().y) < t_shape0.getRadius())
	{
		return 1;
	}

	return 0;
}

int DronsEngine::isCircleAndPointCollide(sf::Vector2f t_point0, sf::Vector2f t_shape0_position, float t_shape0_radius)
{
	if (distance(t_point0.x, t_point0.y, t_shape0_position.x, t_shape0_position.y) < t_shape0_radius)
	{
		return 1;
	}

	return 0;
}

float DronsEngine::lerp(float t_a, float t_b, float t_t)
{
	return t_a * (1 - t_t) + t_b * t_t;
}
