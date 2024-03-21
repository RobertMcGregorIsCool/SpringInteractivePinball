/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>
#pragma once

#include <SFML/Graphics.hpp>

#include "PinballAud.h"
#include "Table.h"
#include "Ball.h"

#define _USE_MATH_DEFINES	// Ehh, why not.
#include <math.h>			// Go the whole hog. Be bigger than god.

class Render
{
public:

	Render(sf::RenderWindow& t_window, Table& t_table, PinballAud& t_pinballAud); // , Collision& t_col);
	~Render();

	void render(Ball t_balls[4], sf::Text t_scoreBoard);

	sf::Texture m_texPartyLand;

	Table& m_table;
	PinballAud& m_pinballAud;

	sf::RenderWindow& m_window; // main SFML window
	sf::View m_view; // View onto table
	sf::Vector2f m_viewCenterAtStart;

	sf::RectangleShape m_floorImage;
	sf::RectangleShape m_backgroundImage; // backgroundImage
	float m_backgroundImageThickness = -8.0f;

	sf::VertexArray m_flipperLine{ sf::Lines }; // Line to show flipper angle

	sf::VertexArray m_mouseLine{ sf::Lines };
	sf::VertexArray m_mouseLineReflect{ sf::Lines };

	void tableKick(float scalar = 1.0f);
	bool screenSettle(sf::Time t_deltaTime);
	void visualDebugLines(sf::Vector2i t_mouseCur);

	bool m_kickTest = false;

private:
	
	const float m_flipperDegree = { (0.0f + 180.0f) * (static_cast<float>(M_PI) / 180.0f) }; // Used to show flipper angle
	sf::Vector2f m_flipperDir = { sin(m_flipperDegree), cos(m_flipperDegree) };// Used to show flipper angle
	// PinballAud m_pinballAudio;

	float m_viewReturnSpeed = 32.0f;
};

