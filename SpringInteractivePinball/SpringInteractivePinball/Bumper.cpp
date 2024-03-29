/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>
#include "Bumper.h"

/// <summary>
/// Constructor.
/// </summary>
/// <param name="t_radius">The radius of the bumper.</param>
/// <param name="t_fill">I really can't be bothered. Surely the pragmatics and context explain the purpose of the variable?</param>
/// <param name="t_line"></param>
/// <param name="t_hitColor"></param>
/// <param name="t_thickness"></param>
/// <param name="t_position"></param>
Bumper::Bumper(float t_radius, sf::Color t_fill, sf::Color t_line, sf::Color t_hitColor, float t_thickness, sf::Vector2f t_position)
{
	m_bumper.setRadius(48.0f);
	m_bumper.setOrigin(m_bumper.getRadius(), m_bumper.getRadius());
	m_bumper.setFillColor(t_fill);
	m_bumper.setOutlineColor(t_line);
	m_bumper.setOutlineThickness(t_thickness);
	m_bumper.setPosition(t_position);

	m_bumperColor = t_fill;
	m_hitColor = t_hitColor;
}

Bumper::~Bumper(){} /// Probably don't need this. I'll learn more about this stuff later in the course.

/// <summary>
/// Called from Detect() in the Collision class
/// </summary>
/// <param name="t_ball">The current ball of the balls array being tested</param>
/// <param name="leadingPoint">The 'front' of the ball, in the direction of its velocity</param>
/// <param name="t_normalisedDir">Generated in Collision::Detect(), normal of ball current velocity</param>
/// <returns>True value used to fire off tablekick and score increment from Collision::Detect()</returns>
bool Bumper::bumperCheck(Ball& t_ball, sf::Vector2f leadingPoint, sf::Vector2f t_normalisedDir)
{
	float bumperColDist = Hlp::v2fGetMagnitude(leadingPoint - m_bumper.getPosition());

	if (bumperColDist < m_bumper.getRadius() + t_ball.M_RADIUS - M_BUMPER_COLLISION_ADJUSTMENT) /// Aircrash radial collision boyeee.
	{
		m_bumper.setFillColor(m_hitColor); /// Light up on hit

		sf::Vector2f bumperNormal = Hlp::v2fGetNormal(m_bumper.getPosition() - t_ball.getPositionCur()); /// Get normal of bumper wall touching t_ball

		sf::Vector2f reflectionVec = Hlp::v2fReflect(t_normalisedDir, bumperNormal); /// Use dot product to get bounce vector

		t_ball.redirect(reflectionVec);

		return true;
	}
	else
	{
		m_bumper.setFillColor(m_bumperColor); /// If the ball isn't touching the bumper, return to normal colour. I mean, 'color'.
		return false;
	}
}