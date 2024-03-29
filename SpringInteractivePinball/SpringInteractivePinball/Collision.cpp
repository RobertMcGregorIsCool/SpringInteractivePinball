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

/// <summary>
/// Called from Update in Game, handles most of collision calculations
/// </summary>
/// <param name="t_ball">Candidate ball from Balls array, for testing collision</param>
/// <param name="t_mouseCur">Current mouse coordinate in window in pixels</param>
void Collision::detect(Ball& t_ball, sf::Vector2i t_mouseCur)
{
	float wide = static_cast<float>(Globals::WIDTH);
	float high = static_cast<float>(Globals::HEIGHT);

	sf::Vector2f normalisedDir = Hlp::v2fGetNormal(t_ball.getVelocity());

	sf::Vector2f leadingPointOfBall = (normalisedDir * t_ball.M_RADIUS);
	
	leadingPointOfBall = leadingPointOfBall + t_ball.getPositionCur();

	if (m_table.m_launchBoxRect.contains(t_ball.getPositionCur())) /// If the ball's in the launch lane...
	{
		t_ball.addForce(sf::Vector2f(0, -1.0f), (4096.0f * 16.0f) * m_launchBoxScalarFromCommand); /// ...send the ball flying! (If it's m_inPlay)
	}

	if (m_table.m_launchWallRect.contains(leadingPointOfBall)) /// If the dividing wall between the launch box and play area contains the front of the ball...
	{
		boundsCheck(false, t_ball, leadingPointOfBall, /// ...then bounce that ball ouf of there!
			m_table.m_launchWallRect.top,
			m_table.m_launchWallRect.top + m_table.m_launchWallRect.height,
			m_table.m_launchWallRect.left,
			m_table.m_launchWallRect.left + m_table.m_launchWallRect.width);
	}

	boundsCheck(true, t_ball, leadingPointOfBall, 0.0f, high, 0.0f, wide); /// Test ball isn't touching the edges of the table - if so, bounce it away.

	if (m_table.m_gutterWallLeftRect.contains(leadingPointOfBall)) /// If the gutter wall contains the leading point of the ball...
	{
		m_table.m_gutterWallLeft.setFillColor(sf::Color::Green); /// Visual feedback for debug.

		boundsCheck(false, t_ball, leadingPointOfBall, /// Bounce the ball away.
			m_table.m_gutterWallLeft.getGlobalBounds().top,
			m_table.m_gutterWallLeft.getGlobalBounds().top + m_table.m_gutterWallLeft.getGlobalBounds().height,
			m_table.m_gutterWallLeft.getGlobalBounds().left,
			m_table.m_gutterWallLeft.getGlobalBounds().left + m_table.m_gutterWallLeft.getGlobalBounds().width);
			m_render.tableKick(2.f); /// Little bit of tableshake.
	}
	else
	{
		m_table.m_gutterWallLeft.setFillColor(sf::Color(99, 79, 23, 255)); /// Return debug color to default color
	}

	if (m_table.m_gutterWallRigtRect.contains(leadingPointOfBall)) /// AUUUGH REPEATED CODE I'M SO SORRY. 
	{
		m_table.m_gutterWallRigt.setFillColor(sf::Color::Green); /// FUCK, THIS IS SHITTY.

		boundsCheck(false, t_ball, leadingPointOfBall,
			m_table.m_gutterWallRigt.getGlobalBounds().top,
			m_table.m_gutterWallRigt.getGlobalBounds().top + m_table.m_gutterWallRigt.getGlobalBounds().height,
			m_table.m_gutterWallRigt.getGlobalBounds().left,
			m_table.m_gutterWallRigt.getGlobalBounds().left + m_table.m_gutterWallRigt.getGlobalBounds().width);
		m_render.tableKick(2.f); /// I'm really just too tired to turn this into a repeatable function, sorry.
	}
	else
	{
		m_table.m_gutterWallRigt.setFillColor(sf::Color(99, 79, 23, 255));
	}

	if (!m_table.m_noCollideLaunchRect.contains(t_ball.getPositionCur()) && !m_table.m_noCollideGutterARect.contains(t_ball.getPositionCur()))
	{/// If the ball isn't in a 'No Collide' Rect, then do the awesome Pete check against the rounded edges of the table.
		inverseRadCheck(t_ball, leadingPointOfBall, normalisedDir, m_table.m_roundedTopBot);
	}

	if(leadingPointOfBall.y > m_gutterHeight)
	{/// If the ball is within the gutter, take it out of play and return it to the starting position.
		t_ball.reset();
		t_ball.setInPlay(false);
		m_globals.m_score = 0;
	}

	if (m_table.m_launchKickerRect.contains(t_ball.getPositionCur()))
	{/// When the ball reaches the top of the launch box, kick it with random force either left or right.
		sf::Vector2f kickDirection (Hlp::randomRange(-1.0f, 1.0f), 0.0f);
		t_ball.addForce(kickDirection, M_LAUNCH_KICKER_FORCE);
	}
	
	/// Flipper / Ball collisions handled here!
	m_table.m_flipLeft.flipperCheck(t_ball, normalisedDir, leadingPointOfBall);
	m_table.m_flipRigt.flipperCheck(t_ball, normalisedDir, leadingPointOfBall);
	m_table.m_flipLeftHigh.flipperCheck(t_ball, normalisedDir, leadingPointOfBall);

	/// Bumper / Ball collisions handled here - if they happen, kick the table and increment the score!
	if (m_table.m_bump01.bumperCheck(t_ball, leadingPointOfBall, normalisedDir) ||
		m_table.m_bump02.bumperCheck(t_ball, leadingPointOfBall, normalisedDir) ||
		m_table.m_bump03.bumperCheck(t_ball, leadingPointOfBall, normalisedDir) ||
		m_table.m_bump04.bumperCheck(t_ball, leadingPointOfBall, normalisedDir) ||
		m_table.m_bump05.bumperCheck(t_ball, leadingPointOfBall, normalisedDir))
	{
		m_render.tableKick();
		m_globals.m_score += M_SCORE_INCREMENT;
	}
}

/// <summary>
/// Test if ball has passed a specified rectangular boundary and reflect the ball
/// </summary>
/// <param name="interior">Is the test against the inside or outside of a box?</param>
/// <param name="t_ball">Ball from the array currently being tested</param>
/// <param name="t_point">Leading point of the ball given direction of travel</param>
/// <param name="top">Top boundary</param>
/// <param name="bottom">Bottom boundary</param>
/// <param name="left">Left boundary</param>
/// <param name="right">Right boundary</param>
void Collision::boundsCheck(bool interior, Ball& t_ball, sf::Vector2f t_point, float top, float bottom, float left, float right)
{
	if (interior)
	{
		if (t_point.x <= left || t_point.x >= right)
		{/// If it's a horizontal boundary...
			t_ball.setVelocity(sf::Vector2f(t_ball.getVelocity().x * -1, t_ball.getVelocity().y)); /// ...flip the X velocity.
		}
		
		if (t_point.y <= top || t_point.y >= bottom)
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
		else if (t_ball.getPositionCur().x > right)
		{
			t_ball.setVelocity(sf::Vector2f(t_ball.getVelocity().x * -1, t_ball.getVelocity().y));
		}
		else if (t_ball.getPositionCur().y < top)
		{
			t_ball.setVelocity(sf::Vector2f(t_ball.getVelocity().x, t_ball.getVelocity().y * -1));
		}
		else if (t_ball.getPositionCur().y > bottom)
		{
			t_ball.setVelocity(sf::Vector2f(t_ball.getVelocity().x, t_ball.getVelocity().y * -1));
		}
	}
}

/// <summary>
/// Awesome Pete reversed radial collision to test curved surfaces on table.
/// </summary>
/// <param name="t_ball">Ball from the array currently being tested</param>
/// <param name="t_leadingPoint">Leading point of the ball given direction of travel</param>
/// <param name="t_normalisedDir">Normalised value of ball velocity</param>
/// <param name="t_outerRing">The circleshape we're testing against</param>
void Collision::inverseRadCheck(Ball& t_ball, sf::Vector2f t_leadingPoint, sf::Vector2f t_normalisedDir, sf::CircleShape& t_outerRing)
{
	float outerColDist = Hlp::v2fGetMagnitude(t_leadingPoint - t_outerRing.getPosition());

	if (outerColDist > t_outerRing.getRadius() - t_ball.M_RADIUS + M_OUTERRING_COLLISION_ADJUSTMENT) /// The reverse of an Air Crash.
	{
		sf::Vector2f outerRingNormal = Hlp::v2fGetNormal(t_ball.getPositionCur() - t_outerRing.getPosition()); /// Get normal of interaction...

		sf::Vector2f reflectionVec = Hlp::v2fReflect(t_normalisedDir, outerRingNormal); /// ...generate reflection vector from normal...

		t_ball.redirect(reflectionVec); /// ...redirect ball along reflection vector.
	}
}

/// <summary>
/// Sends the ball flying up the launch alley.
/// </summary>
/// <param name="t_balls">Ball from the array currently being launched</param>
void Collision::launch(Ball t_balls[4])
{
	for (int i = 0; i < 4; i++) // Magic number here (4) from Game to avoid circular reference. MEA CULPA!
	{
		if (m_table.m_launchBoxRect.contains(t_balls[i].getPositionCur()))
		{
			t_balls[i].setInPlay(true);
		}
	}
	
}

/// <summary>
/// This setter was intended to be used with the mouse wheel to scale the launch power -
/// not working as intended, but I've left it in just in case I come back to this.
/// </summary>
/// <param name="t_scalar">0-1 to scale the launch power.</param>
void Collision::setLaunchBoxScalarFromCommand(float t_scalar)
{
	m_launchBoxScalarFromCommand = t_scalar;
}



