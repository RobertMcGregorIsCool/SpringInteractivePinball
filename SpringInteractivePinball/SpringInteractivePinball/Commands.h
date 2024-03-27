/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>

#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Hlp.h"
#include "Render.h"
#include "Collision.h"
#include "Globals.h"

class Commands
{
public:

	const float M_LAUNCH_PERIOD = 1.0f;
	float m_launchTimer = 0.0f;
	const float M_LAUNCH_TIMER_SPEED = 0.75f;
	const float M_LAUNCH_WHEEL_INCREMENT = 0.2f;

	bool m_pressedLaunch = false;
	bool m_pressedLeftFlip = false;
	bool m_pressedRigtFlip = false;
	bool m_pressedNudge = false;

	const float M_NUDGE_THRESHOLD = 500.0f;

	Collision& m_col;
	Table& m_table;
	Globals& m_globals;

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

