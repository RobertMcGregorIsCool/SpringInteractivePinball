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

	sf::CircleShape		m_flipperDetect;
	sf::RectangleShape	m_flipperVisual;
	sf::CircleShape		m_outerRing;

	bool				m_pointingRigt = false;

	float				m_angleBottom;
	float				m_angleAtRest;
	float				m_angleTop;
};

