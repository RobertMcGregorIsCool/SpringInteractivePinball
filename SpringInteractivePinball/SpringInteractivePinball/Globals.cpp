/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>

#include "Globals.h"

Globals::Globals()
{
	m_timeScalar = 1.0f;
}

Globals::~Globals()
{
}

void Globals::scaleTimeCheck(float input)
{
	m_timeScalar += input;

	if (m_timeScalar < 0.0f)
	{
		m_timeScalar = 0.0f;
	}

	if (m_timeScalar > 1.0f)
	{
		m_timeScalar = 1.0f;
	}
}