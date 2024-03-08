#pragma once
#include <SFML/Graphics.hpp>
class Ball
{
public:

	Ball();
	Ball(float t_radius, sf::Vector2f t_startPos);
	~Ball();

	sf::Sprite ballSprite;
	sf::CircleShape ballShape;
	float m_radius = 1.0f;

	sf::Vector2f m_posStart;

	sf::Vector2f m_position;
	sf::Vector2f m_direction;

	float m_force = 0.0f;
	const float M_GRAVITY = 0.05f;
	const float M_FRICTION = 0.99f;

	void move();

private:
	
};