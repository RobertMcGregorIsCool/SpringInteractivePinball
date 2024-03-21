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
	Collision(Table& t_table, Render& t_render);
	~Collision();

	void detect(Ball& t_ball, sf::Vector2i t_mouseCur);
	void boundsCheck(bool interior, Ball& t_ball, sf::Vector2f t_point, float top, float bottom, float left, float right);
	void bumperCheck(Ball& t_ball, sf::Vector2f t_leadingPoint, sf::Vector2f t_normalisedDir, sf::CircleShape& t_bumper);
	void inverseRadCheck(Ball& t_ball, sf::Vector2f t_leadingPoint, sf::Vector2f t_normalisedDir, sf::CircleShape& t_outerRing);
	void launch(Ball t_balls[4]);
	void flipperCheck(Ball t_ball, sf::CircleShape& t_flipper, float t_max, float t_min); // IMPORTANT! This is probably going to need the ball passed by reference!
	
	void setLaunchBoxScalarFromCommand(float t_scalar);

	Table& m_table;
	Render& m_render;
	

	

	const float M_BUMPER_COLLISION_ADJUSTMENT = 16.0f;

	const float M_LAUNCH_KICKER_FORCE = 100.0f;

private:	
	
	float m_launchBoxScalarFromCommand = 1.0f;
	
};

