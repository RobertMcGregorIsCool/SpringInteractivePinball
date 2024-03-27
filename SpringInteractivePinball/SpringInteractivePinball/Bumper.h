/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>
#pragma once
#include "Ball.h"
class Bumper
{
	const float M_BUMPER_COLLISION_ADJUSTMENT = 16.0f;

public:
	Bumper(float t_radius, sf::Color t_fill, sf::Color t_line, sf::Color t_hitColor, float t_thickness, sf::Vector2f t_position);
	~Bumper();

	bool bumperCheck(Ball& t_ball, sf::Vector2f leadingPoint, sf::Vector2f t_normalisedDir); // , Render t_render);

	sf::CircleShape m_bumper;

	sf::Color m_fill;
	sf::Color m_hitColor;
};

