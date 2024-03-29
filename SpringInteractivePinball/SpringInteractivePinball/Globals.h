/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
/// </summary>

#pragma once

 class Globals
{
public:
	Globals();
	~Globals();

	void scaleTimeCheck(float input);

	float m_timeScalar; // Used to scale deltaTime for slowmo

	int m_score = 0;
	bool debug = false;

	/// <summary>
	/// Game window resolution
	/// </summary>
	static const unsigned int WIDTH = 600U;
	static const unsigned int HEIGHT = 960U;
};