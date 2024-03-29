/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
/// </summary>
#include <iostream>

#include "Render.h"
#include "Globals.h"
#include "Hlp.h"

Render::Render(sf::RenderWindow& t_window, Table& t_table, PinballAud& t_pinballAud, Globals& t_globals) : m_window(t_window), m_table(t_table), m_pinballAud{ t_pinballAud }, m_globals{ t_globals } //, Collision& t_col) : m_window(t_window), m_collision(t_col)
{


	if (!m_texPartyLand.loadFromFile("ASSETS\\IMAGES\\partyLand.gif"))
	{
		std::cout << "Load fail partyland.gif \n\n";
	}

	m_backgroundImage.setOutlineColor(sf::Color(26, 32, 39, 200));
	/// m_backgroundImage.setTexture(&m_texPartyLand); Might reuse this if I polish the project.
	m_backgroundImage.setFillColor(sf::Color(41, 51, 61, 255));
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

	if (m_globals.debug)
	{
		sf::Vertex point;
		point.color = sf::Color::Blue;
		m_flipperLine.clear();
		point.position = m_table.m_flipRigt.getPosition();
		m_flipperLine.append(point);
		point.position = m_table.m_flipRigt.getPosition() + (m_flipperDir * m_table.m_flipRigt.getRadius());
		m_flipperLine.append(point);
	}
}

Render::~Render(){}
/// <summary>
/// Render the game
/// </summary>
/// <param name="t_balls">Current ball in the Balls array</param>
/// <param name="t_scoreBoard"></param>
void Render::render(Ball t_balls[4], sf::Text t_scoreBoard)
{
	if (!m_globals.debug)
	{
		m_window.clear(sf::Color::Black);
		m_window.draw(m_floorImage);
		m_window.draw(m_backgroundImage);
	}
	
	m_window.draw(m_table.m_roundedTopBot);
	if (m_globals.debug)
	{
		m_window.draw(m_table.m_launchBox);
		m_window.draw(m_table.m_launchKicker);
		m_window.draw(m_table.m_noCollideLaunch);
		m_window.draw(m_table.m_flipLeft.m_flipperDetect);
		m_window.draw(m_table.m_flipRigt.m_flipperDetect);
		m_window.draw(m_table.m_flipLeftHigh.m_flipperDetect);
		m_window.draw(m_table.m_gutterWallLeft);
		m_window.draw(m_table.m_gutterWallRigt);

		m_window.draw(m_flipperLine);

		m_window.draw(m_mouseLine);
		m_window.draw(m_mouseLineReflect);
		m_window.draw(m_flippedBallTrajectory);
	}
	
	m_window.draw(m_table.m_noCollideGutterA);
	m_window.draw(m_table.m_launchWall);

	m_window.draw(t_balls[0].m_ballShape);

	m_window.draw(m_ballLine);
	m_window.draw(m_ballLineReflect);

	m_window.draw(m_table.m_flipLeft.m_flipperVisual);
	m_window.draw(m_table.m_flipRigt.m_flipperVisual);
	m_window.draw(m_table.m_flipLeftHigh.m_flipperVisual);

	m_window.draw(m_table.m_bump01.m_bumper);
	m_window.draw(m_table.m_bump02.m_bumper);
	m_window.draw(m_table.m_bump03.m_bumper);
	m_window.draw(m_table.m_bump04.m_bumper);
	m_window.draw(m_table.m_bump05.m_bumper);
	
	m_window.draw(t_scoreBoard);

	m_window.display();

	if (m_kickTest)
	{
		tableKick();
		m_kickTest = false;
	}
}

/// <summary>
/// Provide feedback through screenshake
/// </summary>
/// <param name="scalar">How much kick</param>
void Render::tableKick(float scalar)
{
	float moveRandom = static_cast<float>(Hlp::randomRange(50.0f, -50.0f) * scalar);
	m_view.move(sf::Vector2f(moveRandom, moveRandom));

	if (m_globals.debug)
	{
		float rotRandom = static_cast<float>(Hlp::randomRange(-0.001f, 0.001f) * scalar);
		m_view.rotate(rotRandom);
		float zoomRandom = static_cast<float>(Hlp::randomRange(-0.0125f, 0.0125f) * scalar);
		m_view.zoom(zoomRandom);

		sf::Vector2i newWindowPos = m_window.getPosition() + sf::Vector2i(0, 30);
		m_window.setPosition(newWindowPos);
	}
	
	m_window.setView(m_view);

	m_pinballAud.m_sndRattle.play();
}

/// <summary>
/// Called from Game in Update if the screen is not settled.
/// </summary>
/// <param name="t_deltaTime">Delta time</param>
/// <returns>If settled true, else continue to settle</returns>
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

/// <summary>
/// Lines to help plan trajectories - for debugging
/// </summary>
/// <param name="t_mouseCur">Current position of mouse cursor in pixels</param>
void Render::visualDebugLines(sf::Vector2i t_mouseCur)
{
	sf::Vector2f m_mouseCurFloat = sf::Vector2f(static_cast<float>(t_mouseCur.x), static_cast<float>(t_mouseCur.y));

	sf::Vertex point;
	point.color = sf::Color::Red;
	m_mouseLine.clear();
	point.position = m_table.m_flipRigt.getPosition();
	m_mouseLine.append(point);
	point.position = m_mouseCurFloat;
	m_mouseLine.append(point);

	point.color = sf::Color::Yellow;
	m_mouseLineReflect.clear();
	point.position = m_mouseCurFloat;
	m_mouseLineReflect.append(point);
	sf::Vector2f lineBounce = m_table.m_flipRigt.getPosition() - m_mouseCurFloat;
	lineBounce = Hlp::v2fPerpendicularClockwise(lineBounce);

	point.position = m_mouseCurFloat + lineBounce;
	m_mouseLineReflect.append(point);
}