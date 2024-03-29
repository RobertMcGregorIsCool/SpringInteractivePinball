/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
/// </summary>

#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Ball.h"

#define _USE_MATH_DEFINES	// Ehh, why not.
#include <math.h>			// Go the whole hog. Be bigger than god.

/// <summary>
/// Flipper collision calcs moved into their own class so it can be
/// instantiated around the table.
/// </summary>
class Flipper
{// Private stuff goes here.
	bool m_flipperPressed = false;

public:
	Flipper(bool t_pointingRigt, float t_radius, sf::Vector2f t_position, float t_angleBottom, float t_angleAtRest, float t_angleTop, sf::CircleShape t_outerRing);
	~Flipper();

	void setFlipperPressed(bool pressed);

	void flipperCheck(Ball& t_ball, sf::Vector2f t_normalisedDir, sf::Vector2f t_leadingPoint);

	void flipperHit(Ball& t_ball, sf::Vector2f t_diffBetweenBallAndFlipper);

	void flipperRoll(Ball& t_ball, sf::Vector2f t_normalisedDir);

	sf::Vector2f getPosition();
	float getRadius();

	sf::CircleShape		m_flipperDetect;	/// Debug visual representation and data structure for radial collision with ball(s)
	sf::RectangleShape	m_flipperVisual;	/// Visual representation of flipper - has no physical interaction
	sf::CircleShape		m_outerRing;		/// Table curved surface, used with offset to allow ball interact with flipper at rest

	bool				m_pointingRigt = false; /// Flag to change calculations/visuals depending on flipper facing

	float				m_angleBottom;		/// Bottom of detection zone for flipper
	float				m_angleAtRest;		/// Angle for flipper at rest
	float				m_angleTop;			/// Top of detection zone for flipper
};

