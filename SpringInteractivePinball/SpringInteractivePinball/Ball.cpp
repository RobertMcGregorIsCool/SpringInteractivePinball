#include "Ball.h"
#include "Game.h"
#include <SFML/Graphics.hpp>

Ball::Ball()
{
}

Ball::Ball(Game& t_game)
{
	game = t_game;

	ballShape.setFillColor(sf::Color::Red);
	ballShape.setRadius(M_RADIUS);
	ballShape.setPosition(M_POS_START);
	ballShape.setOrigin(M_RADIUS, M_RADIUS);
}

//Ball::Ball()
//{
//	
// ballShape.setFillColor(sf::Color::Red);
// ballShape.setRadius(M_RADIUS);
// ballShape.setPosition(M_POS_START);
// ballShape.setOrigin(M_RADIUS, M_RADIUS);
//}


Ball::~Ball()
{
}

//void Ball::Initialise(float t_radius, sf::Vector2f t_startPos)
//{
//	
//}




void Ball::addForce(sf::Vector2f t_dir, float t_speed)
{
	m_velocityCur += (t_dir * t_speed);
	
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
{// Continually called in Update()?
	m_positionNxt = m_positionCur + (m_velocityCur * t_deltaTime.asSeconds());// Multiply this by deltatime?

	m_positionCur = Game::testPos(m_positionNxt);

	ballShape.setPosition(m_positionCur);
}
