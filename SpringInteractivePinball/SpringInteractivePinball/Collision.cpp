#include "Collision.h"
#include "Globals.h"
#include "Hlp.h"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

Collision::Collision()
{
}

Collision::~Collision()
{
}

void Collision::setupCollision()
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

void Collision::collision()
{
	sf::Vector2f normalisedDir = Hlp::v2fGetNormal(m_balls[0].getVelocity());
	sf::Vector2f leadingPointOfBall = (normalisedDir * m_balls[0].M_RADIUS);
	leadingPointOfBall = leadingPointOfBall + m_balls[0].getPositionCur();

	if (m_testBoxRect.contains(leadingPointOfBall))
	{
		m_testBox.setFillColor(sf::Color::Green);

		if (m_balls[0].getPositionCur().x < m_testBox.getGlobalBounds().left)
		{
			m_balls[0].bounceCardinal(true);
		}
		else if (m_balls[0].getPositionCur().x > m_testBox.getGlobalBounds().left + m_testBox.getGlobalBounds().width)
		{
			m_balls[0].bounceCardinal(true);
		}
		else if (m_balls[0].getPositionCur().y < m_testBox.getGlobalBounds().top)
		{
			m_balls[0].bounceCardinal(false);
		}
		else
		{
			m_balls[0].bounceCardinal(false);
		}
		tableKick(2.f);
		//sf::Vector2i newWindowPos = m_window.getPosition() + sf::Vector2i(0, 30);
		//m_window.setPosition(newWindowPos);
	}
	else
	{
		m_testBox.setFillColor(sf::Color::Yellow);
	}

	float bumperColDist = Hlp::v2fGetMagnitude(m_balls[0].getPositionCur() - m_bumper01.getPosition());

	if (bumperColDist < m_bumper01.getRadius() + m_balls[0].M_RADIUS)
	{
		m_bumper01.setFillColor(sf::Color::Blue);

		sf::Vector2f bumperNormal = Hlp::v2fGetNormal(m_bumper01.getPosition() - m_balls[0].getPositionCur());

		sf::Vector2f reflectionVec = Hlp::v2fReflect(normalisedDir, bumperNormal);

		m_balls[0].redirect(reflectionVec);

		tableKick(3.0f);
	}
	else
	{
		m_bumper01.setFillColor(sf::Color::Cyan);
	}

	sf::Vector2f m_mouseCurFloat = sf::Vector2f(static_cast<float>(m_mouseCur.x), static_cast<float>(m_mouseCur.y));
	if (Hlp::v2fGetMagnitude(m_flipperTest.getPosition() - m_balls[0].getPositionCur()) < m_flipperTest.getRadius())
	{
		m_testVec02 = Hlp::v2fGetNormal(m_balls[0].getPositionCur() - m_flipperTest.getPosition());

		sf::Vector2f straightUp {0.0f, 1.0f};
		float flipperAngleR = atan2(Hlp::v2fCrossProduct(straightUp, m_testVec02), Hlp::v2fDotProduct(straightUp, m_testVec02));
		float flipperAngleD = flipperAngleR * 180.0f / M_PI;
		flipperAngleD += 180.0f;
		std::cout << "The angle is " << flipperAngleD << ".\n\n";

		m_flipperTest.setFillColor(sf::Color::Cyan);

		if (flipperAngleD < 300.0f && flipperAngleD > 240.0f)
		{
			m_flipperTest.setFillColor(sf::Color::Green);
		}
	}
	else
	{
		m_flipperTest.setFillColor(sf::Color(220, 220, 220, 255));
	}

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
