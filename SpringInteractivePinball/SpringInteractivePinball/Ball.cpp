/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
/// 
/// So, I did function comments in the .h file, but probably won't do that again.
/// </summary>

#include "Ball.h"

Ball::Ball()
{/// Settin' stuff up.
	m_ballShape.setFillColor(sf::Color(127, 127, 127, 255));
	m_ballShape.setRadius(M_RADIUS);
	m_ballShape.setPosition(M_POS_START);
	m_ballShape.setOrigin(M_RADIUS, M_RADIUS);
}

Ball::~Ball(){} /// Don't think we're using this as we're not doing memory managment, but why not?

void Ball::addForce(sf::Vector2f t_dir, float t_speed)
{/// Me apeing Unity. Combines direction and speed into a velocity, clamps it for safety.
	m_velocityCur += (t_dir * t_speed);
	m_velocityCur = Hlp::v2fClamp(m_velocityMax, -m_velocityMax, m_velocityCur);
}

void Ball::redirect(sf::Vector2f t_dir)
{
	sf::Vector2f normalDir = Hlp::v2fGetNormal(t_dir);
	m_velocityCur = normalDir * Hlp::v2fGetMagnitude(m_velocityCur);
}

void Ball::flipperImpact(sf::Vector2f t_dir)
{
	sf::Vector2f flipperDir = Hlp::v2fGetNormal(t_dir);
	m_velocityCur += flipperDir * Hlp::v2fGetMagnitude(m_velocityCur);
}

void Ball::update(sf::Time t_deltaTime)
{// Continually called in Game::Update()?
	if (m_inPlay)
	{
		addForce(sf::Vector2f(0.0f, 1.0f), M_GRAVITY * 256.0f);

		m_velocityCur *= M_FRICTION;

		m_positionNxt = m_positionCur + (m_velocityCur * t_deltaTime.asSeconds());
	}
}

void Ball::setPosition(sf::Vector2f newPosition) 
{
	if (m_inPlay)
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
		// Sprite.setPosition(newPosition) will go here soon. (But it never did)
	}
}

void Ball::setInPlay(bool play)
{
	m_inPlay = play;
}

void Ball::teleport(sf::Vector2f t_newPosition)
{
	m_positionNxt = t_newPosition;
	setPosition(t_newPosition);
	setVelocity(sf::Vector2f(0.0f, 0.0f));
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

void Ball::reset()
{
	teleport(M_POS_START);
}