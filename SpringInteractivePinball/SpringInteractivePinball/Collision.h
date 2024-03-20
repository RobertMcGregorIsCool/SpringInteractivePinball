/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "Ball.h"

#define _USE_MATH_DEFINES	// Ehh, why not.
#include <math.h>			// Go the whole hog. Be bigger than god.

class Collision
{
public:
	Collision();
	~Collision();

	void detect(Ball& t_ball, sf::Vector2i t_mouseCur);
	void boundsCheck(bool interior, Ball& t_ball, sf::Vector2f t_point, float top, float bottom, float left, float right);
	void bumperCheck(Ball& t_ball, sf::Vector2f t_leadingPoint, sf::Vector2f t_normalisedDir, sf::CircleShape& t_bumper);
	void flipperCheck(Ball t_ball, sf::CircleShape& t_flipper, float t_max, float t_min);
	void visualDebugLines(sf:: Vector2i t_mouseCur);

	sf::RectangleShape m_testBox;

	sf::CircleShape m_roundedTopBot;

	sf::CircleShape m_bumper01;

	sf::CircleShape m_flipperTest;
	sf::VertexArray m_flipperLine{sf::Lines}; // Line to show flipper angle

	sf::VertexArray m_mouseLine {sf::Lines};
	sf::VertexArray m_mouseLineReflect {sf::Lines};

	const float M_BUMPER_COLLISION_ADJUSTMENT = 16.0f;

	bool m_kickTest = false;

private:	
	sf::Rect<float> m_testBoxRect;

	const float m_flipperDegree = { (0.0f + 180.0f) * (static_cast<float>(M_PI) / 180.0f) }; // Used to show flipper angle
	sf::Vector2f m_flipperDir = { sin(m_flipperDegree), cos(m_flipperDegree) };// Used to show flipper angle
};

