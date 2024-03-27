/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>
#include "Collision.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>

Collision::Collision(Table& t_table, Render& t_render, Globals& t_globals) : m_table{ t_table }, m_render{ t_render }, m_globals{ t_globals } {}

Collision::~Collision(){}

void Collision::detect(Ball& t_ball, sf::Vector2i t_mouseCur)
{
	float wide = static_cast<float>(Globals::WIDTH);
	float high = static_cast<float>(Globals::HEIGHT);

	sf::Vector2f normalisedDir = Hlp::v2fGetNormal(t_ball.getVelocity());

	sf::Vector2f leadingPointOfBall = (normalisedDir * t_ball.M_RADIUS);
	
	leadingPointOfBall = leadingPointOfBall + t_ball.getPositionCur();

	if (m_table.m_launchBoxRect.contains(t_ball.getPositionCur()))
	{
		t_ball.addForce(sf::Vector2f(0, -1.0f), (4096.0f * 16.0f) * m_launchBoxScalarFromCommand);
	}

	if (m_table.m_launchWallRect.contains(leadingPointOfBall))
	{
		boundsCheck(false, t_ball, leadingPointOfBall,
			m_table.m_launchWallRect.top,
			m_table.m_launchWallRect.top + m_table.m_launchWallRect.height,
			m_table.m_launchWallRect.left,
			m_table.m_launchWallRect.left + m_table.m_launchWallRect.width);
	}

	boundsCheck(true, t_ball, leadingPointOfBall, 0.0f, high, 0.0f, wide);

	if (m_table.m_gutterWallLeftRect.contains(leadingPointOfBall))
	{
		m_table.m_gutterWallLeft.setFillColor(sf::Color::Green);

		boundsCheck(false, t_ball, leadingPointOfBall,
			m_table.m_gutterWallLeft.getGlobalBounds().top,
			m_table.m_gutterWallLeft.getGlobalBounds().top + m_table.m_gutterWallLeft.getGlobalBounds().height,
			m_table.m_gutterWallLeft.getGlobalBounds().left,
			m_table.m_gutterWallLeft.getGlobalBounds().left + m_table.m_gutterWallLeft.getGlobalBounds().width);
			m_render.tableKick(2.f);
			//sf::Vector2i newWindowPos = m_window.getPosition() + sf::Vector2i(0, 30);
			//m_window.setPosition(newWindowPos);
	}
	else
	{
		m_table.m_gutterWallLeft.setFillColor(sf::Color(99, 79, 23, 255));
	}

	bumperCheck(t_ball, leadingPointOfBall, normalisedDir, m_table.m_bumper01);

	if (!m_table.m_noCollideLaunchRect.contains(t_ball.getPositionCur()) && !m_table.m_noCollideGutterARect.contains(t_ball.getPositionCur()))
	{
		inverseRadCheck(t_ball, leadingPointOfBall, normalisedDir, m_table.m_roundedTopBot);
	}

	if(leadingPointOfBall.y > m_gutterHeight)
	{
		t_ball.reset();
		t_ball.setInPlay(false);
	}

	if (m_table.m_launchKickerRect.contains(t_ball.getPositionCur()))
	{
		sf::Vector2f kickDirection (Hlp::randomRange(-1.0f, 1.0f), 0.0f);
		t_ball.addForce(kickDirection, M_LAUNCH_KICKER_FORCE);
	}
	
	m_table.m_flipRigt.flipperCheck(t_ball, normalisedDir, leadingPointOfBall);
	// flipperCheck(t_ball, m_table.m_flipperRigt, 300.0f, 240.0f, 260.0f, leadingPointOfBall, normalisedDir, m_table.m_roundedTopBot); // 260 <-flipper at rest
}

void Collision::boundsCheck(bool interior, Ball& t_ball, sf::Vector2f t_point, float top, float bottom, float left, float right)
{
	if (interior)
	{
		if (t_point.x <= left || t_point.x >= right) // (leadingPointOfBall.x <= 0.0f || leadingPointOfBall.x >= wide)
		{
			t_ball.setVelocity(sf::Vector2f(t_ball.getVelocity().x * -1, t_ball.getVelocity().y));
		}
		
		if (t_point.y <= top || t_point.y >= bottom) // (leadingPointOfBall.y <= 0.0f || leadingPointOfBall.y >= high)
		{
			t_ball.setVelocity(sf::Vector2f(t_ball.getVelocity().x, t_ball.getVelocity().y * -1));
		}
	} 
	else
	{
		if (t_ball.getPositionCur().x < left)
		{
			t_ball.setVelocity(sf::Vector2f(t_ball.getVelocity().x * -1, t_ball.getVelocity().y));
		}
		else if (t_ball.getPositionCur().x > right) // (leadingPointOfBall.x <= 0.0f || leadingPointOfBall.x >= wide))
		{
			t_ball.setVelocity(sf::Vector2f(t_ball.getVelocity().x * -1, t_ball.getVelocity().y));
		}
		else if (t_ball.getPositionCur().y < top)
		{
			t_ball.setVelocity(sf::Vector2f(t_ball.getVelocity().x, t_ball.getVelocity().y * -1));
		}
		else if (t_ball.getPositionCur().y > bottom)// (leadingPointOfBall.y <= 0.0f || leadingPointOfBall.y >= high)
		{
			t_ball.setVelocity(sf::Vector2f(t_ball.getVelocity().x, t_ball.getVelocity().y * -1));
		}
	}
}

void Collision::bumperCheck(Ball& t_ball, sf::Vector2f leadingPoint, sf::Vector2f t_normalisedDir, sf::CircleShape& t_bumper)
{
	float bumperColDist = Hlp::v2fGetMagnitude(leadingPoint - t_bumper.getPosition());

	if (bumperColDist < t_bumper.getRadius() + t_ball.M_RADIUS - M_BUMPER_COLLISION_ADJUSTMENT)
	{
		t_bumper.setFillColor(sf::Color::Blue);

		sf::Vector2f bumperNormal = Hlp::v2fGetNormal(t_bumper.getPosition() - t_ball.getPositionCur());

		sf::Vector2f reflectionVec = Hlp::v2fReflect(t_normalisedDir, bumperNormal);

		t_ball.redirect(reflectionVec);

		m_render.tableKick(3.0f);
	}
	else
	{
		t_bumper.setFillColor(sf::Color::Cyan);
	}
}

void Collision::inverseRadCheck(Ball& t_ball, sf::Vector2f t_leadingPoint, sf::Vector2f t_normalisedDir, sf::CircleShape& t_outerRing)
{
	float outerColDist = Hlp::v2fGetMagnitude(t_leadingPoint - t_outerRing.getPosition());

	if (outerColDist > t_outerRing.getRadius() - t_ball.M_RADIUS + M_BUMPER_COLLISION_ADJUSTMENT)
	{
		sf::Vector2f outerRingNormal = Hlp::v2fGetNormal(t_ball.getPositionCur() - t_outerRing.getPosition());

		sf::Vector2f reflectionVec = Hlp::v2fReflect(t_normalisedDir, outerRingNormal);

		t_ball.redirect(reflectionVec);
	}
}

void Collision::launch(Ball t_balls[4])
{
	for (int i = 0; i < 4; i++) // Magic number here from Game to avoid circular reference. FIX!
	{
		if (m_table.m_launchBoxRect.contains(t_balls[i].getPositionCur()))
		{
			t_balls[i].setInPlay(true);
		}
	}
	
}

void Collision::setLaunchBoxScalarFromCommand(float t_scalar)
{
	m_launchBoxScalarFromCommand = t_scalar;
}



