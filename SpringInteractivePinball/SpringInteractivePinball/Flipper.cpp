/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>

#include "Flipper.h"
// t_angleTop/Max 300.0f, t_angleBottom/Min 240.0f, t_angleAtRest/Resting 260.0f,
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

	m_pointingRigt = t_pointingRigt;
	m_angleBottom  = t_angleBottom;
	m_angleAtRest = t_angleAtRest;
	m_angleTop = t_angleTop;
	m_outerRing = t_outerRing;
}

Flipper::~Flipper(){}

void Flipper::setFlipperPressed(bool t_pressed)
{
	m_flipperPressed = t_pressed;
	if (m_flipperPressed)
	{
		m_flipperVisual.setRotation(m_angleTop + 90.0f);
	}
	else
	{
		m_flipperVisual.setRotation(m_angleAtRest + 90.0f);
	}
}

void Flipper::flipperCheck(Ball& t_ball, sf::Vector2f t_normalisedDir, sf::Vector2f t_leadingPoint)
{// t_angleTop/Max 300.0f, t_angleBottom/Min 240.0f, t_angleAtRest/Resting 260.0f,
	if (Hlp::v2fGetMagnitude(m_flipperDetect.getPosition() - t_ball.getPositionCur()) < m_flipperDetect.getRadius() + t_ball.M_RADIUS)
	{
		sf::Vector2f diffBetweenBallAndFlipper = t_ball.getPositionCur() - m_flipperDetect.getPosition();
		sf::Vector2f flipperToBallNormal = Hlp::v2fGetNormal(diffBetweenBallAndFlipper);
		float flipperToBallMag = Hlp::v2fGetMagnitude(diffBetweenBallAndFlipper);

		sf::Vector2f straightUp{ 0.0f, 1.0f };
		float flipperAngleR = atan2(Hlp::v2fCrossProduct(straightUp, flipperToBallNormal), Hlp::v2fDotProduct(straightUp, flipperToBallNormal));
		float flipperAngleD = flipperAngleR * 180.0f / static_cast<float>(M_PI);
		flipperAngleD += 180.0f;

		m_flipperDetect.setFillColor(sf::Color(0, 255, 255, 100)); // Cyan

		if (flipperAngleD < m_angleTop && flipperAngleD > m_angleBottom)
		{
			if (m_flipperPressed)
			{
				m_flipperDetect.setFillColor(sf::Color(255, 0, 0, 100)); // Red
				sf::Vector2f lineBounce = diffBetweenBallAndFlipper;
				lineBounce = Hlp::v2fPerpendicularAntiClockwise(lineBounce);
				// m_render.visualDebugBall(t_ball.getPositionCur(), lineBounce);
				t_ball.flipperImpact(lineBounce);
			}
			else
			{
				m_flipperDetect.setFillColor(sf::Color(0, 255, 0, 100)); // Green
			}
		}
		if (flipperAngleD < m_angleAtRest && flipperAngleD > m_angleBottom)
		{
			m_flipperDetect.setFillColor(sf::Color(255, 0, 0, 100)); // Orange.

			sf::Vector2f outerRingNormal = Hlp::v2fGetNormal(t_ball.getPositionCur() - m_outerRing.getPosition());

			sf::Vector2f reflectionVec = Hlp::v2fReflect(t_normalisedDir, outerRingNormal);

			t_ball.redirect(reflectionVec);
		}
	}
	else
	{
		m_flipperDetect.setFillColor(sf::Color(220, 220, 220, 100)); // Uhh, grey?
	}
}

//void Collision::flipperCheck(Ball& t_ball, sf::CircleShape& t_flipper, float t_max, float t_min, float t_resting, sf::Vector2f t_leadingPoint, sf::Vector2f t_normalisedDir, sf::CircleShape& t_outerRing)//, bool t_active)
//{
//	// m_render.visualDebugFlipper(t_ball, t_leadingPoint); // The only reason I have the t_leadingPoint param is for visual debug.
//
//	if (Hlp::v2fGetMagnitude(t_flipper.getPosition() - t_ball.getPositionCur()) < t_flipper.getRadius() + t_ball.M_RADIUS)
//	{
//		sf::Vector2f diffBetweenBallAndFlipper = t_ball.getPositionCur() - t_flipper.getPosition();
//		sf::Vector2f flipperToBallNormal = Hlp::v2fGetNormal(diffBetweenBallAndFlipper);
//		float flipperToBallMag = Hlp::v2fGetMagnitude(diffBetweenBallAndFlipper);
//
//		sf::Vector2f straightUp{ 0.0f, 1.0f };
//		float flipperAngleR = atan2(Hlp::v2fCrossProduct(straightUp, flipperToBallNormal), Hlp::v2fDotProduct(straightUp, flipperToBallNormal));
//		float flipperAngleD = flipperAngleR * 180.0f / static_cast<float>(M_PI);
//		flipperAngleD += 180.0f;
//
//		t_flipper.setFillColor(sf::Color(0, 255, 255, 100)); // Cyan	
//
//		if (flipperAngleD < t_max && flipperAngleD > t_min)
//		{
//			if (m_rigtFlipperActive)
//			{
//				t_flipper.setFillColor(sf::Color(255, 0, 0, 100)); // Red
//				sf::Vector2f lineBounce = diffBetweenBallAndFlipper;
//				lineBounce = Hlp::v2fPerpendicularAntiClockwise(lineBounce);
//				// m_render.visualDebugBall(t_ball.getPositionCur(), lineBounce);
//				t_ball.flipperImpact(lineBounce);
//			}
//			else
//			{
//				t_flipper.setFillColor(sf::Color(0, 255, 0, 100)); // Green
//			}
//		}
//
//		if (flipperAngleD < t_resting && flipperAngleD > t_min)
//		{
//			t_flipper.setFillColor(sf::Color(255, 0, 0, 100)); // Orange.
//
//			sf::Vector2f outerRingNormal = Hlp::v2fGetNormal(t_ball.getPositionCur() - t_outerRing.getPosition());
//
//			sf::Vector2f reflectionVec = Hlp::v2fReflect(t_normalisedDir, outerRingNormal);
//
//			t_ball.redirect(reflectionVec);
//		}
//	}
//	else
//	{
//		t_flipper.setFillColor(sf::Color(220, 220, 220, 100)); // Uhh, grey?
//	}
//}