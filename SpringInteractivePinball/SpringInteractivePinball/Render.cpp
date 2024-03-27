/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>
#include <iostream>

#include "Render.h"
#include "Globals.h"
#include "Hlp.h"

Render::Render(sf::RenderWindow& t_window, Table& t_table, PinballAud& t_pinballAud) : m_window(t_window), m_table(t_table), m_pinballAud{ t_pinballAud } //, Collision& t_col) : m_window(t_window), m_collision(t_col)
{


	if (!m_texPartyLand.loadFromFile("ASSETS\\IMAGES\\partyLand.gif"))
	{
		std::cout << "Load fail partyland.gif \n\n";
	}

	m_backgroundImage.setOutlineColor(sf::Color(26, 32, 39, 200)); // (sf::Color::Magenta);
	m_backgroundImage.setTexture(&m_texPartyLand);
	// m_backgroundImage.setFillColor(sf::Color(41, 51, 61, 255)); // (sf::Color::White);
	m_backgroundImage.setOutlineThickness(m_backgroundImageThickness);
	m_backgroundImage.setSize(sf::Vector2f(Globals::WIDTH, Globals::HEIGHT));
	m_backgroundImage.setOrigin(sf::Vector2f(Globals::WIDTH * 0.5f, Globals::HEIGHT * 0.5f));
	m_backgroundImage.setPosition(sf::Vector2f(Globals::WIDTH * 0.5f, Globals::HEIGHT * 0.5f));

	m_floorImage.setFillColor(sf::Color::Black);
	m_floorImage.setSize(sf::Vector2f(Globals::WIDTH * 2.0f, Globals::HEIGHT * 2.0f));
	m_floorImage.setOrigin(sf::Vector2f(Globals::WIDTH, Globals::HEIGHT));
	m_floorImage.setPosition(sf::Vector2f(Globals::WIDTH, Globals::HEIGHT));

	m_view.setCenter(Globals::WIDTH * 0.5f, Globals::HEIGHT * 0.5f);
	m_viewCenterAtStart = m_view.getCenter();
	m_view.reset(sf::FloatRect(0.0f, 0.0f, Globals::WIDTH, Globals::HEIGHT));

	m_window.setView(m_view);

	sf::Vertex point;
	point.color = sf::Color::Blue;
	m_flipperLine.clear();
	point.position = m_table.m_flipperRigt.getPosition();
	m_flipperLine.append(point);
	point.position = m_table.m_flipperRigt.getPosition() + (m_flipperDir * m_table.m_flipperRigt.getRadius());
	m_flipperLine.append(point);
}

Render::~Render(){}

void Render::render(Ball t_balls[4], sf::Text t_scoreBoard)
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_floorImage);
	m_window.draw(m_backgroundImage);
	m_window.draw(m_table.m_roundedTopBot);
	m_window.draw(m_table.m_launchBox);
	m_window.draw(m_table.m_launchKicker);
	// m_window.draw(m_table.m_noCollideLaunch);
	
	
	
	m_window.draw(m_table.m_noCollideGutterA);
	// m_window.draw(m_table.m_gutterTeleport); Not needed!
	m_window.draw(m_table.m_launchWall);

	
	m_window.draw(m_flipperLine);
	
	//m_window.draw(m_mouseLine);
	//m_window.draw(m_mouseLineReflect);

	m_window.draw(t_balls[0].m_ballShape);

	m_window.draw(m_ballLine);
	m_window.draw(m_ballLineReflect);

	//m_window.draw(m_table.m_flipperRigt);
	// m_window.draw(m_table.m_flipperVisualRigt);
	m_window.draw(m_table.m_flipRigt.m_flipperDetect);
	m_window.draw(m_table.m_flipRigt.m_flipperVisual);

	m_window.draw(m_flippedBallTrajectory);

	m_window.draw(m_table.m_gutterWallLeft);
	m_window.draw(m_table.m_gutterWallRigt);
	
	m_window.draw(m_table.m_bumper01);
	
	m_window.draw(t_scoreBoard);


	m_window.display();

	if (m_kickTest)
	{
		tableKick();
		m_kickTest = false;
	}
}

void Render::tableKick(float scalar)
{
	float moveRandom = static_cast<float>(Hlp::randomRange(50.0f, -50.0f) * scalar);
	m_view.move(sf::Vector2f(moveRandom, moveRandom));
	//float rotRandom = static_cast<float>(Hlp::randomRange(-0.001f, 0.001f) * scalar);
	//m_view.rotate(rotRandom);
	//float zoomRandom = static_cast<float>(Hlp::randomRange(-0.0125f, 0.0125f) * scalar);
	//m_view.zoom(zoomRandom);
	m_window.setView(m_view);

	m_pinballAud.m_sndRattle.play();

	// std::cout << "Random number is " << Hlp::randomRange(-50.0f, 50.0f) << "\n";
}

bool Render::screenSettle(sf::Time t_deltaTime)
{
	if (m_view.getCenter() == sf::Vector2f(Globals::WIDTH * 0.5f, Globals::HEIGHT * 0.5f) && m_view.getRotation() == 0.0f && m_view.getSize() == sf::Vector2f(Globals::WIDTH, Globals::HEIGHT))
	{
		return true;
	}
	else
	{
		m_view.setCenter(Hlp::v2fLerp(m_view.getCenter(), sf::Vector2f(Globals::WIDTH * 0.5f, Globals::HEIGHT * 0.5f), t_deltaTime.asSeconds() * m_viewReturnSpeed));
		m_view.setRotation(Hlp::floatLerp(m_view.getRotation(), 0.0f, t_deltaTime.asSeconds() * m_viewReturnSpeed));
		m_view.setSize(Hlp::v2fLerp(m_view.getSize(), sf::Vector2f(Globals::WIDTH, Globals::HEIGHT), t_deltaTime.asSeconds() * m_viewReturnSpeed));

		m_window.setView(m_view);
		return false;
	}
}

void Render::visualDebugLines(sf::Vector2i t_mouseCur)
{
	sf::Vector2f m_mouseCurFloat = sf::Vector2f(static_cast<float>(t_mouseCur.x), static_cast<float>(t_mouseCur.y));

	sf::Vertex point;
	point.color = sf::Color::Red;
	m_mouseLine.clear();
	point.position = m_table.m_flipperRigt.getPosition();
	m_mouseLine.append(point);
	point.position = m_mouseCurFloat;
	m_mouseLine.append(point);

	point.color = sf::Color::Yellow;
	m_mouseLineReflect.clear();
	point.position = m_mouseCurFloat;
	m_mouseLineReflect.append(point);
	sf::Vector2f lineBounce = m_table.m_flipperRigt.getPosition() - m_mouseCurFloat;
	lineBounce = Hlp::v2fPerpendicularClockwise(lineBounce);

	point.position = m_mouseCurFloat + lineBounce;
	m_mouseLineReflect.append(point);
}

void Render::visualDebugFlipper(Ball t_ball, sf::Vector2f t_leadingPos)
{
	// std::cout << "I'm being called!\n";
	sf::Vertex point;
	point.color = sf::Color::Magenta;
	m_ballLine.clear();
	point.position = m_table.m_flipperRigt.getPosition();
	m_ballLine.append(point);
	point.position = t_ball.getPositionCur();
	m_ballLine.append(point);

	point.color = sf::Color(255, 255, 0, 255);
	m_ballLineReflect.clear();
	point.position = t_ball.getPositionCur();
	m_ballLineReflect.append(point);
	sf::Vector2f lineBounce = m_table.m_flipperRigt.getPosition() - t_ball.getPositionCur();
	lineBounce = Hlp::v2fPerpendicularClockwise(lineBounce);

	point.position = t_ball.getPositionCur() + lineBounce;
	m_ballLineReflect.append(point);
}

void Render::visualDebugBall(sf::Vector2f t_position, sf::Vector2f t_lineBounce)
{
	sf::Vertex point;
	point.color = sf::Color::Cyan;
	m_flippedBallTrajectory.clear();
	
	point.position = t_position;
	m_flippedBallTrajectory.append(point);
	
	point.position = t_position + t_lineBounce;
	m_flippedBallTrajectory.append(point);
}

