#include "Ball.h"
#include <SFML/Graphics.hpp>

Ball::Ball()
{
}

Ball::Ball(float t_radius = 1.0f, sf::Vector2f t_startPos = sf::Vector2f(300.0f, 500.0f))
{
	m_posStart = t_startPos;
	m_radius = t_radius;
	
	ballShape.setFillColor(sf::Color::Red);
	ballShape.setRadius(m_radius);
	ballShape.setPosition(t_startPos);
}


Ball::~Ball()
{
}

void Ball::move()
{
}
