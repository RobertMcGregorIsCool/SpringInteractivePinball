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
	
	sf::Vector2f m_positionNxt;	// Originally for collision test, should be excised.
	const float M_RADIUS = 16.0f; // Ball radius

	sf::CircleShape m_ballShape;
	
	Ball();

	~Ball();

	/// <summary>
	/// This is called by ForceZones (eg. launcher) and interactables (eg.
	/// flippers, bumpers etc) to add spd to current speed & change dir
	/// </summary>
	/// <param name="dir"></param>
	/// <param name="speed"></param>
	/// <returns></returns>
	void addForce(sf::Vector2f t_dir, float t_speed); // Preceding block comment is borked, just going to write 'em like this.

	void redirect (sf::Vector2f t_dir); // Will this show up elsewhere?

	void flipperImpact(sf::Vector2f t_dir);

	void update(sf::Time t_deltaTime);

	void setPosition(sf::Vector2f t_newPosition);

	void setInPlay(bool play);

	void teleport(sf::Vector2f t_newPosition);

	sf::Vector2f getVelocity();
	void setVelocity(sf::Vector2f t_velocity);
	sf::Vector2f getPositionCur();

	void reset();

private:
	sf::Sprite ballSprite;

	const sf::Vector2f M_POS_START = sf::Vector2f(Globals::WIDTH * 0.96f, Globals::HEIGHT * 0.95f);

	sf::Vector2f m_velocityCur = sf::Vector2f{ 0.0f,0.0f };
	const float	m_velocityMax = 1000.0f;

	sf::Vector2f m_positionCur = M_POS_START;

	sf::Vector2f m_direction;

	float		m_force = 0.0f;
	const float M_GRAVITY = 0.05f;
	const float M_FRICTION = 0.99f;
	bool		m_inPlay = false;
};