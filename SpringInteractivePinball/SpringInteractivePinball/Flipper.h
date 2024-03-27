/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>

#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Ball.h"

#define _USE_MATH_DEFINES	// Ehh, why not.
#include <math.h>			// Go the whole hog. Be bigger than god.

class Flipper
{
// Private stuff goes here.
	bool m_flipperPressed = false;
	

public:
	Flipper(bool t_pointingRigt, float t_radius, sf::Vector2f t_position, float t_angleBottom, float t_angleAtRest, float t_angleTop, sf::CircleShape t_outerRing);
	~Flipper();

	void setFlipperPressed(bool pressed);

	// void flipperCheck(Ball& t_ball, sf::CircleShape& t_flipper, float t_max, float t_min, float t_resting, sf::Vector2f t_leadingPoint, sf::Vector2f t_normalisedDir, sf::CircleShape& t_outerRing);
	void flipperCheck(Ball& t_ball, sf::Vector2f t_normalisedDir, sf::Vector2f t_leadingPoint);

	sf::CircleShape		m_flipperDetect;
	sf::RectangleShape	m_flipperVisual;

	bool m_pointingRigt = false;
	//float t_radius = 0.0f;
	//sf::Vector2f m_position;
	float m_angleBottom;
	float m_angleAtRest;
	float m_angleTop;
	sf::CircleShape m_outerRing;
};

