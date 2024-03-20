/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>

#include "Ball.h"

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

void Ball::update(sf::Time t_deltaTime)
{// Continually called in Game::Update()?
	addForce(sf::Vector2f(0.0f, 1.0f), M_GRAVITY * 256.0f);

	m_velocityCur *= M_FRICTION;

	m_positionNxt = m_positionCur + (m_velocityCur * t_deltaTime.asSeconds());// Multiply this by deltatime?
}

void Ball::setPosition(sf::Vector2f newPosition) 
{
	m_positionCur = newPosition;

	if (m_positionCur.x < 0.0f)
	{
		m_positionCur.x = 0.0f;
	}
	if (m_positionCur.x > Globals::WIDTH)
	{
		m_positionCur.x = Globals::WIDTH;
	}
	if (m_positionCur.y < 0.0f)
	{
		m_positionCur.y = 0.0f;
	}
	if (m_positionCur.y > Globals::HEIGHT)
	{
		m_positionCur.y = Globals::HEIGHT;
	}

	m_ballShape.setPosition(newPosition);
	// Sprite.setPosition(newPosition) will go here soon.
}

sf::Vector2f Ball::getVelocity()
{
	return m_velocityCur;
}

void Ball::setVelocity(sf::Vector2f t_velocity)
{
	m_velocityCur = t_velocity;	
}

sf::Vector2f Ball::getPositionCur()
{
	return m_positionCur;
}







