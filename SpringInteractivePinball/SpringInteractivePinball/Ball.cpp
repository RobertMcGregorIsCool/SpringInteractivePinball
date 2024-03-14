/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>

#include "Ball.h"
#include "Game.h"
#include "Hlp.h"
#include <SFML/Graphics.hpp>


Ball::Ball()
{
	m_ballShape.setFillColor(sf::Color(127,127,127,255));
	m_ballShape.setRadius(M_RADIUS);
	m_ballShape.setPosition(M_POS_START);
	m_ballShape.setOrigin(M_RADIUS, M_RADIUS);
}


Ball::~Ball()
{
}

void Ball::addForce(sf::Vector2f t_dir, float t_speed)
{
	m_velocityCur += (t_dir * t_speed);
	m_velocityCur = Hlp::v2fClamp(m_velocityMax, -m_velocityMax, m_velocityCur);
}

void Ball::redirect(sf::Vector2f t_dir)
{
	sf::Vector2f normalDir = Hlp::v2fGetNormal(t_dir);
	m_velocityCur = normalDir * Hlp::v2fGetMagnitude(m_velocityCur);
}

void Ball::bounceCardinal(bool horizontal)
{
	if (horizontal)
	{
		m_velocityCur.x *= -1;
	}
	else
	{
		m_velocityCur.y *= -1;
	}
}


void Ball::move(sf::Time t_deltaTime)
{// Continually called in Game::Update()?
	m_positionNxt = m_positionCur + (m_velocityCur * t_deltaTime.asSeconds());// Multiply this by deltatime?
}

void Ball::setPosition(sf::Vector2f newPosition) 
{
	m_positionCur = newPosition;

	m_ballShape.setPosition(newPosition);
	// Sprite.setPosition(newPosition) will go here soon.
}

sf::Vector2f Ball::getVelocity()
{
	return m_velocityCur;
}

sf::Vector2f Ball::getPositionCur()
{
	return m_positionCur;
}







