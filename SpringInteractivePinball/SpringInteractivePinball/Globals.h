/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>

#pragma once

static class Globals
{
public:
	Globals();
	~Globals();

	void scaleTimeCheck(float input);

	float m_timeScalar;

	int m_score = 0;
	bool debug = false;

	static const unsigned int WIDTH = 600U;
	static const unsigned int HEIGHT = 960U;
};