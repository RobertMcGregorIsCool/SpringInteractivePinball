/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
/// </summary>

#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Hlp.h"
#include "Globals.h"


class Ball
{
public:
	
	sf::Vector2f m_positionNxt;	/// Originally for collision test, should be excised.
	const float M_RADIUS = 16.0f; /// Ball radius

	sf::CircleShape m_ballShape; /// Round shape to represent ball in game.
	
	Ball(); /// Constructor!

	~Ball();/// Destructor!

	/// <summary>
	/// This is called by ForceZones (eg. launcher) and interactables (eg.
	/// flippers, bumpers etc) to add spd to current speed & change dir
	/// </summary>
	/// <param name="dir"></param>
	/// <param name="speed"></param>
	/// <returns></returns>
	void addForce(sf::Vector2f t_dir, float t_speed); /// Preceding block comment is borked, just going to write 'em like this.

	void redirect (sf::Vector2f t_dir); /// Send ball in t_dir w/current mag, overwrites cur_velocity

	void flipperImpact(sf::Vector2f t_dir); /// Similar to redirect() but adds new velocity to cur_velocity

	void update(sf::Time t_deltaTime);/// Called from Game::Update, applies gravity, friction & velocity.

	void setPosition(sf::Vector2f t_newPosition);///If in play - final bounds check, apply new position to ball.

	void setInPlay(bool play);/// Used to change bool - whether ball should move/have physics applied.

	void teleport(sf::Vector2f t_newPosition);/// Jump ball to t_newPosition on table, eliminates velocity.

	sf::Vector2f getVelocity(); /// Returns current ball velocity.
	void setVelocity(sf::Vector2f t_velocity); /// Sets current ball velocity.
	sf::Vector2f getPositionCur(); /// Returns global postion.

	void reset(); /// Uses teleport to move ball to initial position.

private:

	const sf::Vector2f M_POS_START = sf::Vector2f(Globals::WIDTH * 0.96f, Globals::HEIGHT * 0.95f); /// Starting pos derived from screen size.

	sf::Vector2f m_velocityCur = sf::Vector2f{ 0.0f,0.0f }; /// The current velocity. I question the need to comment every var.
	
	const float	m_velocityMax = 1000.0f; /// Used to clamp m_velocityCur during addForce()

	sf::Vector2f m_positionCur = M_POS_START; /// At the start, the current position is the starting position. Sigh.
	
	const float M_GRAVITY = 0.05f; /// Gravity value applied to ball.
	
	const float M_FRICTION = 0.99f; /// Friction value applied to ball.
	
	bool		m_inPlay = false;	/// Determines if the ball can move, if physics etc is applied.
};