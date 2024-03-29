/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
/// </summary>

#include "Flipper.h"
// Reference for developer: t_angleTop/Max 300.0f, t_angleBottom/Min 240.0f, t_angleAtRest/Resting 260.0f,

/// <summary>
/// Physics emulation of pinball flipper, intended to send ball flying OR
/// allow ball to rest on flipper and roll towards gutter.
/// </summary>
/// <param name="t_pointingRigt">Is the flipper pointing right?</param>
/// <param name="t_radius">Unrefined detection radius</param>
/// <param name="t_position">Placement of flipper on the table</param>
/// <param name="t_angleBottom">Bottom of detection zone for flipper</param>
/// <param name="t_angleAtRest">Angle for flipper at rest</param>
/// <param name="t_angleTop">Top of detection zone for flipper</param>
/// <param name="t_outerRing">Table curved surface, used with offset to allow ball interact with flipper at rest</param>
Flipper::Flipper(bool t_pointingRigt, float t_radius, sf::Vector2f t_position, float t_angleBottom, float t_angleAtRest, float t_angleTop, sf::CircleShape t_outerRing)
{ // Radius is usually 80.0f
	m_flipperDetect.setRadius(t_radius);
	m_flipperDetect.setOrigin(t_radius, t_radius);
	m_flipperDetect.setFillColor(sf::Color(220, 220, 220, 150));
	m_flipperDetect.setOutlineColor(sf::Color::Black);
	m_flipperDetect.setOutlineThickness(1.0f);
	m_flipperDetect.setPosition(t_position);

	m_flipperVisual.setSize(sf::Vector2f(t_radius, 15.0f));
	m_flipperVisual.setOrigin(m_flipperVisual.getSize().x, m_flipperVisual.getSize().y * 0.5f); // This will depend on t_pointingRigt
	m_flipperVisual.setFillColor(sf::Color::Blue);
	m_flipperVisual.setPosition(m_flipperDetect.getPosition().x, m_flipperDetect.getPosition().y);
	m_flipperVisual.setRotation(t_angleAtRest + 90.0f); // Rotation is t_restDegrees + 90f // 260.0f

	m_pointingRigt	= t_pointingRigt;
	m_angleBottom	= t_angleBottom;
	m_angleAtRest	= t_angleAtRest;
	m_angleTop		= t_angleTop;
	m_outerRing		= t_outerRing;
}

Flipper::~Flipper(){}

/// <summary>
/// Set flag for whether the flipper is active,
/// also change visual rotation for the flipper
/// </summary>
/// <param name="t_pressed">Is the flipper button pressed or not?</param>
void Flipper::setFlipperPressed(bool t_pressed)
{
	m_flipperPressed = t_pressed;
	if (m_flipperPressed)
	{
		m_flipperVisual.setRotation(m_angleTop + 90.0f); /// Visual flipper rotation
	}
	else
	{
		m_flipperVisual.setRotation(m_angleAtRest + 90.0f);
	}
}

/// <summary>
/// Is the ball detected by the flipper? And if so, react 
/// appropriately according to the state of the flipper
/// </summary>
/// <param name="t_ball">Current ball from Balls array</param>
/// <param name="t_normalisedDir">Direction from t_ball velocity</param>
/// <param name="t_leadingPoint">Front point of ball considering direction</param>
void Flipper::flipperCheck(Ball& t_ball, sf::Vector2f t_normalisedDir, sf::Vector2f t_leadingPoint)
{
	if (Hlp::v2fGetMagnitude(m_flipperDetect.getPosition() - t_ball.getPositionCur()) < m_flipperDetect.getRadius() + t_ball.M_RADIUS)
	{/// If within the radius...
		sf::Vector2f diffBetweenBallAndFlipper = t_ball.getPositionCur() - m_flipperDetect.getPosition(); /// Get displacement.
		sf::Vector2f flipperToBallNormal = Hlp::v2fGetNormal(diffBetweenBallAndFlipper); /// Get normal.
		float flipperToBallMag = Hlp::v2fGetMagnitude(diffBetweenBallAndFlipper); /// Get magnitude.

		sf::Vector2f straightUp{ 0.0f, 1.0f };
		float flipperAngleR = atan2(Hlp::v2fCrossProduct(straightUp, flipperToBallNormal), Hlp::v2fDotProduct(straightUp, flipperToBallNormal)); /// Get radians
		float flipperAngleD = flipperAngleR * 180.0f / static_cast<float>(M_PI); /// Convert to degrees
		flipperAngleD += 180.0f;

		m_flipperDetect.setFillColor(sf::Color(0, 255, 255, 100)); /// Cyan

		if (m_pointingRigt) /// Detection bifurcates depending on flipper orientation
		{
			if (flipperAngleD > m_angleAtRest && flipperAngleD < m_angleBottom)
			{/// Ball is above rest level, so ball rolls.
				flipperRoll(t_ball, t_normalisedDir);
			}
			else if (flipperAngleD > m_angleTop && flipperAngleD < m_angleBottom)
			{/// Ball is within flippper detection angles
				flipperHit(t_ball, diffBetweenBallAndFlipper);
			}
		}
		else
		{
			if (flipperAngleD < m_angleAtRest && flipperAngleD > m_angleBottom)
			{
				flipperRoll(t_ball, t_normalisedDir);
			}
			else if (flipperAngleD < m_angleTop && flipperAngleD > m_angleBottom)
			{
				flipperHit(t_ball, diffBetweenBallAndFlipper);
			}
		}
	}
	else
	{
		m_flipperDetect.setFillColor(sf::Color(220, 220, 220, 100)); /// Uhh, grey?
	}
}

/// <summary>
/// React by bouncing or sending the ball flying from impact
/// </summary>
/// <param name="t_ball">Current ball from Balls array</param>
/// <param name="t_diffBetweenBallAndFlipper">Vector difference</param>
void Flipper::flipperHit(Ball& t_ball, sf::Vector2f t_diffBetweenBallAndFlipper)
{
	if (m_flipperPressed)
	{
		m_flipperDetect.setFillColor(sf::Color(255, 0, 0, 100)); /// Red
		sf::Vector2f lineBounce = t_diffBetweenBallAndFlipper;
		if (m_pointingRigt)
		{/// Pointing Right
			lineBounce = Hlp::v2fPerpendicularClockwise(lineBounce);
		}
		else
		{/// Pointing Left
			lineBounce = Hlp::v2fPerpendicularAntiClockwise(lineBounce);
		}
		
		t_ball.flipperImpact(lineBounce);
	}
	else
	{
		m_flipperDetect.setFillColor(sf::Color(0, 255, 0, 100)); /// Green
	}
}

/// <summary>
/// React by allowing the ball to roll down the flipper
/// </summary>
/// <param name="t_ball">Current ball from Balls array</param>
/// <param name="t_normalisedDir">Normal direction of Ball current velocity</param>
void Flipper::flipperRoll(Ball& t_ball, sf::Vector2f t_normalisedDir)
{
	m_flipperDetect.setFillColor(sf::Color(255, 200, 0, 100)); /// Orange.

	sf::Vector2f outerRingNormal = Hlp::v2fGetNormal(t_ball.getPositionCur() - m_outerRing.getPosition());

	sf::Vector2f reflectionVec = Hlp::v2fReflect(t_normalisedDir, outerRingNormal);

	t_ball.redirect(reflectionVec);
}

/// <summary>
/// Return flipper position
/// </summary>
/// <returns>Flipper position</returns>
sf::Vector2f Flipper::getPosition()
{
	return m_flipperDetect.getPosition();
}

/// <summary>
/// Return flipper radius
/// </summary>
/// <returns>Flipper radius</returns>
float Flipper::getRadius()
{
	return m_flipperDetect.getRadius();
}