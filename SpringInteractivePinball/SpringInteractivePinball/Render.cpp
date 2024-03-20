/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>
#include <iostream>

#include "Render.h"
// #include "Collision.h"
#include "Globals.h"
#include "Hlp.h"
//#include "PinballAud.h"

Render::Render(sf::RenderWindow& t_window, Collision& t_col) : m_window(t_window), m_collision(t_col)
{
	m_backgroundImage.setOutlineColor(sf::Color::Magenta);
	m_backgroundImage.setFillColor(sf::Color::White);
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
}

Render::~Render(){}

void Render::render(Ball t_balls[4], sf::Text t_scoreBoard)
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_backgroundImage);
	m_window.draw(m_floorImage);
	m_window.draw(m_collision.m_roundedTopBot);

	
	
	m_window.draw(m_collision.m_flipperTest);
	m_window.draw(m_collision.m_flipperLine);
	m_window.draw(m_collision.m_mouseLine);
	m_window.draw(m_collision.m_mouseLineReflect);

	m_window.draw(t_balls[0].m_ballShape);

	m_window.draw(m_collision.m_testBox);
	m_window.draw(m_collision.m_bumper01);

	m_window.draw(t_scoreBoard);

	m_window.display();
}

void Render::tableKick(float scalar)
{
	float moveRandom = static_cast<float>(Hlp::randomRange(4.0f, -4.0f) * scalar);
	m_view.move(sf::Vector2f(moveRandom, moveRandom));
	float rotRandom = static_cast<float>(Hlp::randomRange(-0.125f, 0.125f) * scalar);
	m_view.rotate(rotRandom);
	float zoomRandom = static_cast<float>(Hlp::randomRange(-0.125f, 0.125f) * scalar);
	m_view.zoom(zoomRandom);
	m_window.setView(m_view);

	// m_pinballAudio.m_sndRattle.play();

	std::cout << "Random number is " << Hlp::randomRange(-50.0f, 50.0f) << "\n";
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
