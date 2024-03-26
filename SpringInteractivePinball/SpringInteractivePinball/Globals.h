#pragma once

static class Globals
{
public:
	Globals();
	~Globals();

	void scaleTimeCheck(float input);
	
	float m_timeScalar;

	static const unsigned int WIDTH	= 600U;
	static const unsigned int HEIGHT= 960U;
};

