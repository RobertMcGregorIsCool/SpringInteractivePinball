/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
/// </summary>

#pragma once

#include <SFML/Graphics.hpp>

#include "PinballAud.h"
#include "Table.h"
#include "Ball.h"
#include "Globals.h"

#define _USE_MATH_DEFINES	// Ehh, why not.
#include <math.h>			// Go the whole hog. Be bigger than god.

class Render
{
public:

	Render(sf::RenderWindow& t_window, Table& t_table, PinballAud& t_pinballAud, Globals& t_globals); // , Collision& t_col);
	~Render();

	void render(Ball t_balls[4], sf::Text t_scoreBoard);

	sf::Texture m_texPartyLand; /// Reference background

	/// <summary>
	/// References to important instantiated classes
	/// </summary>
	Table&		m_table;		
	PinballAud& m_pinballAud;	
	Globals&	m_globals;		
	sf::RenderWindow& m_window; /// main SFML window
	
	sf::View m_view; /// View onto table
	sf::Vector2f m_viewCenterAtStart; /// Position of view at the start

	sf::RectangleShape m_floorImage; /// So there's something darker when the table moves
	sf::RectangleShape m_backgroundImage; /// backgroundImage
	float m_backgroundImageThickness = -8.0f;

	sf::VertexArray m_flipperLine{ sf::Lines }; /// Line to show flipper angle

	sf::VertexArray m_mouseLine{ sf::Lines };		/// Used for debug.
	sf::VertexArray m_mouseLineReflect{ sf::Lines };/// Used for debug

	sf::VertexArray m_ballLine {sf::Lines };		/// Used for debug. 
	sf::VertexArray m_ballLineReflect{sf::Lines };	/// Used for debug.

	sf::VertexArray m_flippedBallTrajectory {sf::Lines}; /// Used for debug.

	void tableKick(float scalar = 1.0f);
	bool screenSettle(sf::Time t_deltaTime);

	void visualDebugLines(sf::Vector2i t_mouseCur);	

	bool m_kickTest = false; /// Used for debug.

private:
	
	const float m_flipperDegree = { (0.0f + 180.0f) * (static_cast<float>(M_PI) / 180.0f) }; /// Used to show flipper angle
	sf::Vector2f m_flipperDir = { sin(m_flipperDegree), cos(m_flipperDegree) };/// Used to show flipper angle

	float m_viewReturnSpeed = 32.0f; /// Speed at which kicked view of table returns to normal
};

