#include "Ball.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

Ball::Ball()
{
}

Ball::Ball(float t_radius = 1.0f, sf::Vector2f t_startPos = sf::Vector2f(300.0f, 500.0f))
{
	m_posStart = t_startPos;
	m_positionCur = m_posStart;
	m_radius = t_radius;
	
	ballShape.setFillColor(sf::Color::Red);
	ballShape.setRadius(m_radius);
	ballShape.setPosition(t_startPos);
	ballShape.setOrigin(m_radius, m_radius);
}


Ball::~Ball()
{
}


void Ball::addForce(sf::Vector2f t_dir, float t_speed)
{
	m_velocityCur += (t_dir * t_speed);
	
}

void Ball::move()
{// Continually called in Update()?
	m_positionNxt = m_positionCur + m_velocityCur;// Multiply this by deltatime?

	m_positionCur = Game::testPos(m_positionNxt);

	ballShape.setPosition(m_positionCur);
}
