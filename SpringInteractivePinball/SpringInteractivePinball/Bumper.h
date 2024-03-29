/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
/// </summary>

#pragma once
#include "Ball.h"
class Bumper
{
	const float M_BUMPER_COLLISION_ADJUSTMENT = 16.0f; /// Used to allow a little interpenetration with the bumper

public:
	Bumper(float t_radius, sf::Color t_fill, sf::Color t_line, sf::Color t_hitColor, float t_thickness, sf::Vector2f t_position);
	~Bumper();

	bool bumperCheck(Ball& t_ball, sf::Vector2f leadingPoint, sf::Vector2f t_normalisedDir); /// So I guess I'm doing the comments for functions in the Source files now.

	sf::CircleShape m_bumper; /// Sigh. SFML object to represent the bumper.

	sf::Color m_bumperColor;/// Bumper colour.
	sf::Color m_hitColor;	/// ...The colour of the Bumper when it's hit.
};

