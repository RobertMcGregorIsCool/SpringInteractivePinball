/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>

#include "Commands.h"

Commands::Commands(Collision& t_col, Table& t_table, Globals& t_globals) : m_col{ t_col }, m_table{ t_table }, m_globals{ t_globals }
{
}

Commands::~Commands()
{
}

void Commands::update(sf::Time t_deltaTime)
{
	if (m_pressedLaunch && m_launchTimer < M_LAUNCH_PERIOD)
	{
		m_launchTimer += M_LAUNCH_TIMER_SPEED * t_deltaTime.asSeconds();
		m_launchTimer = m_launchTimer > M_LAUNCH_PERIOD ? M_LAUNCH_PERIOD : m_launchTimer;
	}
}

void Commands::prep()
{// Retract plunger - animation and turn on collisions
	std::cout << "Called 'prep'.\n\n";
}

void Commands::launchDn()
{// Release plunger - animation and turn on collisions
	m_pressedLaunch = true;
	std::cout << "Called 'launchDn'.\n\n";
}

void Commands::launchUp(Ball t_balls[4])
{// This should be the timer increasing to 1 as the scalar, using a speed value as increment
	m_pressedLaunch = false;
	std::cout << "Called 'launchUp' with scalar at: " << m_launchTimer << ".\n\n";
	m_col.setLaunchBoxScalarFromCommand(m_launchTimer);
	m_launchTimer = 0.0f;
	m_col.launch(t_balls);
}

void Commands::leftFlipDn()
{// Change collisions
	m_pressedLeftFlip = true;
	m_table.m_flipLeft.setFlipperPressed(m_pressedLeftFlip);
	m_table.m_flipLeftHigh.setFlipperPressed(m_pressedLeftFlip);
}

void Commands::leftFlipUp()
{
	m_pressedLeftFlip = false;
	m_table.m_flipLeft.setFlipperPressed(m_pressedLeftFlip);
	m_table.m_flipLeftHigh.setFlipperPressed(m_pressedLeftFlip);
}

void Commands::nudgeDn(Ball t_ball)
{// Talk to render, change collisions? Addforce on ball?
	std::cout << "Called 'nudge'.\n\n";
	t_ball.addForce(sf::Vector2f(0.0f, -1.0f), M_NUDGE_THRESHOLD * 8.0f); // Hlp::v2fGetNormal(t_ball.getVelocity()), M_NUDGE_THRESHOLD);
}

void Commands::nudgeUp(){}

void Commands::rigtFlipDn()
{// Change collisions
	m_pressedRigtFlip = true;
	m_table.m_flipRigt.setFlipperPressed(m_pressedRigtFlip);
}

void Commands::rigtFlipUp()
{
	m_pressedRigtFlip = false;
	m_table.m_flipRigt.setFlipperPressed(m_pressedRigtFlip);
}

void Commands::teleportBall(Ball& t_ball, sf::Vector2f t_mouseCur)
{
	t_ball.setInPlay(true);
	t_ball.teleport(t_mouseCur);
}

void Commands::newBall()
{// This probably needs to be in Game.

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