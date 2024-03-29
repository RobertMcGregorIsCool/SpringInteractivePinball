/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
/// </summary>

#include "Globals.h"

Globals::Globals()
{
	m_timeScalar = 1.0f;
}

Globals::~Globals(){}

/// <summary>
/// Mostly a setter for m_timeScalar, clamps.
/// </summary>
/// <param name="input">Scale input</param>
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