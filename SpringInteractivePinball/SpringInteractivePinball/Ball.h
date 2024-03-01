/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>
#pragma once

#include <SFML/Graphics.hpp>

class Ball
{
public:
	sf::Sprite ballSprite;
	const float radius = 1.0f;

	sf::Vector2f m_posStart;

	sf::Vector2f m_position;
	sf::Vector2f m_direction;
	
	float m_force = 0.0f;
	const float M_GRAVITY = 0.05f;
	const float M_FRICTION= 0.99f;

	void Ball();

	void move();

private:
	
};
