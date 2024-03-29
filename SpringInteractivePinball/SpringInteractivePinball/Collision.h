/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "Ball.h"
#include "Table.h"
#include "Render.h"
#include "Globals.h"
#include "Hlp.h"

#define _USE_MATH_DEFINES	// Ehh, why not.
#include <math.h>			// Go the whole hog. Be bigger than god.

class Collision
{
public:
	Collision(Table& t_table, Render& t_render, Globals& t_globals);
	~Collision();

	void detect(Ball& t_ball, sf::Vector2i t_mouseCur);
	void boundsCheck(bool interior, Ball& t_ball, sf::Vector2f t_point, float top, float bottom, float left, float right);
	void inverseRadCheck(Ball& t_ball, sf::Vector2f t_leadingPoint, sf::Vector2f t_normalisedDir, sf::CircleShape& t_outerRing);
	void launch(Ball t_balls[4]);
	
	void setLaunchBoxScalarFromCommand(float t_scalar);

	Table&		m_table;	/// Local reference to table layout.
	Render&		m_render;	/// Local reference to renderer class.
	Globals&	m_globals;	/// Local reference yada globals.

	const float M_OUTERRING_COLLISION_ADJUSTMENT = 16.0f; /// Allows a little outerring interpenetration.

	const float M_LAUNCH_KICKER_FORCE = 100.0f; /// Applied to ball at top of launch box, randomly scaled 0-1, left or right.

private:	

	const int M_SCORE_INCREMENT = 200;

	float m_gutterHeight = 930.0f; /// If ball passes this height and not in 'no collide' Rect, it's taken out of play and teleported to the start point.

	float m_launchBoxScalarFromCommand = 1.0f; /// Used by unfinished plunger system to knock ball into play with varying force.
	
};

