#include "Commands.h"

Commands::Commands(Collision& t_col) : m_col{t_col}
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
	std::cout << "Called 'left FlipDn'.\n\n";
}

void Commands::leftFlipUp()
{
	m_pressedLeftFlip = false;
	std::cout << "Called 'leftFlipUp'.\n\n";
}

void Commands::nudgeDn(Ball t_ball)
{// Talk to render, change collisions? Addforce on ball?
	std::cout << "Called 'nudge'.\n\n";
	t_ball.addForce(sf::Vector2f(0.0f, -1.0f), M_NUDGE_THRESHOLD * 8.0f); // Hlp::v2fGetNormal(t_ball.getVelocity()), M_NUDGE_THRESHOLD);
}

void Commands::nudgeUp()
{

}

void Commands::rigtFlipDn()
{// Change collisions
	m_pressedRigtFlip = true;
	std::cout << "Called 'right FlipDn'.\n\n";
}

void Commands::rigtFlipUp()
{
	m_pressedRigtFlip = false;
	std::cout << "Called 'rigtFlipUp'.\n\n";
}

//void Commands::newBall()
//{// This probably needs to be in Game.
//	std::cout << "Called 'new ball'.\n\n";
//}