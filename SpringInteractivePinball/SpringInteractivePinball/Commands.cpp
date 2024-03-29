/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
/// </summary>

#include "Commands.h"

Commands::Commands(Collision& t_col, Table& t_table, Globals& t_globals) : m_col{ t_col }, m_table{ t_table }, m_globals{ t_globals }
{
}

Commands::~Commands()
{
}

/// <summary>
/// Called from Update() in Game, used for the launch timer
/// </summary>
/// <param name="t_deltaTime">Sexy, sexy deltaTime. Framerate independant, you know?</param>
void Commands::update(sf::Time t_deltaTime)
{
	if (m_pressedLaunch && m_launchTimer < M_LAUNCH_PERIOD)
	{
		m_launchTimer += M_LAUNCH_TIMER_SPEED * t_deltaTime.asSeconds();
		m_launchTimer = m_launchTimer > M_LAUNCH_PERIOD ? M_LAUNCH_PERIOD : m_launchTimer;
	}
}

/// <summary>
/// Retract plunger - animation and turn on collisions
/// </summary>
void Commands::prep()
{
	std::cout << "Called 'prep'.\n\n";
}

/// <summary>
/// Release plunger - animation and turn on collisions
/// </summary>
void Commands::launchDn()
{
	m_pressedLaunch = true;
}

/// <summary>
/// This should be the timer increasing to 1 as the scalar, using a speed value as increment
/// </summary>
/// <param name="t_balls">Current ball being handled from Balls array</param>
void Commands::launchUp(Ball t_balls[4])
{
	m_pressedLaunch = false;
	m_col.setLaunchBoxScalarFromCommand(m_launchTimer);
	m_launchTimer = 0.0f;
	m_col.launch(t_balls);
}

/// <summary>
/// Flipper pressed, set flags in related flipper collision.
/// </summary>
void Commands::leftFlipDn()
{
	m_pressedLeftFlip = true;
	m_table.m_flipLeft.setFlipperPressed(m_pressedLeftFlip);
	m_table.m_flipLeftHigh.setFlipperPressed(m_pressedLeftFlip);
}

/// <summary>
/// Flipper released, set flags for flipper collision.
/// </summary>
void Commands::leftFlipUp()
{
	m_pressedLeftFlip = false;
	m_table.m_flipLeft.setFlipperPressed(m_pressedLeftFlip);
	m_table.m_flipLeftHigh.setFlipperPressed(m_pressedLeftFlip);
}

/// <summary>
/// Spacebar pressed, nudge the ball
/// </summary>
/// <param name="t_ball"></param>
void Commands::nudgeDn(Ball t_ball)
{
	t_ball.addForce(sf::Vector2f(0.0f, -1.0f), M_NUDGE_THRESHOLD * 8.0f);
}

/// <summary>
/// Not using this now, but if I go back to it,
/// will use this for more complex nudge behavior.
/// </summary>
void Commands::nudgeUp(){}

/// <summary>
/// Flipper pressed, set flags in related flipper collision.
/// </summary>
void Commands::rigtFlipDn()
{
	m_pressedRigtFlip = true;
	m_table.m_flipRigt.setFlipperPressed(m_pressedRigtFlip);
}

/// <summary>
/// Flipper released, set flags for flipper collision.
/// </summary>
void Commands::rigtFlipUp()
{
	m_pressedRigtFlip = false;
	m_table.m_flipRigt.setFlipperPressed(m_pressedRigtFlip);
}

/// <summary>
/// Places ball on mouse cursor within table
/// </summary>
/// <param name="t_ball">Current ball being handled from Balls array</param>
/// <param name="t_mouseCur">Cursor current position in floatease</param>
void Commands::teleportBall(Ball& t_ball, sf::Vector2f t_mouseCur)
{
	t_ball.setInPlay(true);
	t_ball.teleport(t_mouseCur);
}

/// <summary>
/// Originally intended to help with multiball, now used to turn on
/// debug mode. I'd like to restore intended function if I come back to this.
/// </summary>
void Commands::newBall()
{
	m_globals.debug = !m_globals.debug;
	if (m_globals.debug)
	{
		m_globals.scaleTimeCheck(-0.85f);
	}
	else
	{
		m_globals.scaleTimeCheck(2.0f);
	}
}