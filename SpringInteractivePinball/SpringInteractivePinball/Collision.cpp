/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>
#include "Collision.h"
#include "Globals.h"
#include "Hlp.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <iostream>

Collision::Collision()
{
	m_testBox.setOrigin(100.0f, 100.0f);
	m_testBox.setFillColor(sf::Color::Yellow);
	m_testBox.setSize(sf::Vector2f(200.0f, 200.0f));
	m_testBox.setPosition(Globals::WIDTH * 0.5f, Globals::HEIGHT * 0.75f);

	m_testBoxRect = sf::Rect<float>{ sf::Vector2f((Globals::WIDTH * 0.5f) - 100.0f, (Globals::HEIGHT * 0.75f) - 100.0f), m_testBox.getSize() };

	m_bumper01.setRadius(48.0f);
	m_bumper01.setOrigin(m_bumper01.getRadius(), m_bumper01.getRadius());
	m_bumper01.setFillColor(sf::Color::Cyan);
	m_bumper01.setOutlineColor(sf::Color::Red);
	m_bumper01.setOutlineThickness(-4.0f);
	m_bumper01.setPosition(Globals::WIDTH * 0.5f, Globals::HEIGHT * 0.25f);

	m_roundedTopBot.setRadius(512.0f - 32.0f);
	m_roundedTopBot.setOrigin(m_roundedTopBot.getRadius(), m_roundedTopBot.getRadius());
	m_roundedTopBot.setOutlineColor(sf::Color::Magenta);
	m_roundedTopBot.setFillColor(sf::Color::Transparent);
	m_roundedTopBot.setOutlineThickness(100.0f);
	m_roundedTopBot.setPosition(Globals::WIDTH * 0.5f, Globals::HEIGHT * 0.5f);

	m_flipperTest.setRadius(80.0f);
	m_flipperTest.setOrigin(m_flipperTest.getRadius(), m_flipperTest.getRadius());
	m_flipperTest.setFillColor(sf::Color(220, 220, 220, 255));
	m_flipperTest.setOutlineColor(sf::Color::Black);
	m_flipperTest.setOutlineThickness(1.0f);
	m_flipperTest.setPosition(Globals::WIDTH * 0.5f, Globals::HEIGHT * 0.43f);

	sf::Vertex point;
	point.color = sf::Color::Blue;
	m_flipperLine.clear();
	point.position = m_flipperTest.getPosition();
	m_flipperLine.append(point);
	point.position = m_flipperTest.getPosition() + (m_flipperDir * m_flipperTest.getRadius());
	m_flipperLine.append(point);
}

Collision::~Collision(){}

void Collision::detect(Ball& t_ball, sf::Vector2i t_mouseCur)
{
	/*if (m_kickTest)
	{
		std::cout << "Trying to kick...!\n\n";
		t_ball.bounceCardinal(false);
		m_kickTest = false;
	}*/

	float wide = static_cast<float>(Globals::WIDTH);
	float high = static_cast<float>(Globals::HEIGHT);

	sf::Vector2f normalisedDir = Hlp::v2fGetNormal(t_ball.getVelocity());

	sf::Vector2f leadingPointOfBall = (normalisedDir * t_ball.M_RADIUS);
	
	leadingPointOfBall = leadingPointOfBall + t_ball.getPositionCur();

	boundsCheck(true, t_ball, leadingPointOfBall, 0.0f, high, 0.0f, wide);

	if (m_testBoxRect.contains(leadingPointOfBall))
	{
		m_testBox.setFillColor(sf::Color::Green);

		boundsCheck(false, t_ball, leadingPointOfBall,
			m_testBox.getGlobalBounds().top,
			m_testBox.getGlobalBounds().top + m_testBox.getGlobalBounds().height,
			m_testBox.getGlobalBounds().left,
			m_testBox.getGlobalBounds().left + m_testBox.getGlobalBounds().width);
			//tableKick(2.f);
			//sf::Vector2i newWindowPos = m_window.getPosition() + sf::Vector2i(0, 30);
			//m_window.setPosition(newWindowPos);
	}
	else
	{
		m_testBox.setFillColor(sf::Color::Yellow);
	}

	bumperCheck(t_ball, leadingPointOfBall, normalisedDir, m_bumper01);

	// flipperCheck(t_ball, m_flipperTest, 300.0f, 240.0f);
	flipperCheck(t_ball, m_flipperTest, 120.0f, 60.0f);

	visualDebugLines(t_mouseCur);
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

		//tableKick(3.0f);
	}
	else
	{
		t_bumper.setFillColor(sf::Color::Cyan);
	}
}

void Collision::flipperCheck(Ball t_ball, sf::CircleShape& t_flipper, float t_max, float t_min)
{
	if (Hlp::v2fGetMagnitude(t_flipper.getPosition() - t_ball.getPositionCur()) < t_flipper.getRadius())
	{
		sf::Vector2f flipperToBallNormal = Hlp::v2fGetNormal(t_ball.getPositionCur() - t_flipper.getPosition());

		sf::Vector2f straightUp{ 0.0f, 1.0f };
		float flipperAngleR = atan2(Hlp::v2fCrossProduct(straightUp, flipperToBallNormal), Hlp::v2fDotProduct(straightUp, flipperToBallNormal));
		float flipperAngleD = flipperAngleR * 180.0f / static_cast<float>(M_PI);
		flipperAngleD += 180.0f;

		t_flipper.setFillColor(sf::Color::Cyan);

		if (flipperAngleD < t_max && flipperAngleD > t_min)
		{
			t_flipper.setFillColor(sf::Color::Green);
		}
	}
	else
	{
		t_flipper.setFillColor(sf::Color(220, 220, 220, 255));
	}
}

void Collision::visualDebugLines(sf::Vector2i t_mouseCur)
{
	sf::Vector2f m_mouseCurFloat = sf::Vector2f(static_cast<float>(t_mouseCur.x), static_cast<float>(t_mouseCur.y));

	sf::Vertex point;
	point.color = sf::Color::Red;
	m_mouseLine.clear();
	point.position = m_flipperTest.getPosition();
	m_mouseLine.append(point);
	point.position = m_mouseCurFloat;
	m_mouseLine.append(point);

	point.color = sf::Color::Yellow;
	m_mouseLineReflect.clear();
	point.position = m_mouseCurFloat;
	m_mouseLineReflect.append(point);
	sf::Vector2f lineBounce = m_flipperTest.getPosition() - m_mouseCurFloat;
	lineBounce = Hlp::v2fPerpendicularClockwise(lineBounce);

	point.position = m_mouseCurFloat + lineBounce;
	m_mouseLineReflect.append(point);
}

