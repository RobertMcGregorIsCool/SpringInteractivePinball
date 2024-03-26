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