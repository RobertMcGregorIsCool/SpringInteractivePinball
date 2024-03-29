/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
/// </summary>

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Hlp.h"
#include "Render.h"
#include "Collision.h"
#include "Globals.h"

/// <summary>
/// So, this is a half-assed attempt at creating a command pattern
/// in SFML using the C++ that I currently understand. Ideally this
/// would be using events/delegates/whatever.
/// </summary>
class Commands
{
public:

	const float M_LAUNCH_PERIOD				= 1.0f; /// Used for timer on plunger/ball launch
	float m_launchTimer						= 0.0f; /// Ditto.
	const float M_LAUNCH_TIMER_SPEED		= 0.75f;
	const float M_LAUNCH_WHEEL_INCREMENT	= 0.2f;

	bool m_pressedLaunch	= false; // Used to prevent repeated keypresses when holding down a button.
	bool m_pressedLeftFlip	= false;
	bool m_pressedRigtFlip	= false;
	bool m_pressedNudge		= false;

	const float M_NUDGE_THRESHOLD = 500.0f; // Mouse displacement must exceed this to trigger nudging the table

	Collision&	m_col;		/// Local reference to collision class.
	Table&		m_table;	/// I tell you, internalising C++ referencing is a heckuva thing.
	Globals&	m_globals;

	Commands(Collision& t_col, Table& t_table, Globals& t_globals);
	~Commands();

	void update(sf::Time t_deltaTime);

	void prep();
	void launchDn();
	void launchUp(Ball t_balls[4]);
	void leftFlipDn();
	void leftFlipUp();
	void nudgeDn(Ball t_ball);
	void nudgeUp();
	void rigtFlipDn();
	void rigtFlipUp();
	void newBall();
	void teleportBall(Ball& t_ball, sf::Vector2f t_mouseCur);
};

