#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

#define _USE_MATH_DEFINES	// Ehh, why not.
#include <math.h>			// Go the whole hog. Be bigger than god.

class Collision
{
public:
	Collision();
	~Collision();

	void setupCollision();
	void collision();

	sf::RectangleShape m_testBox;

	sf::CircleShape m_roundedTopBot;

	sf::CircleShape m_bumper01;

	sf::CircleShape m_flipperTest;
	sf::VertexArray m_flipperLine{sf::Lines}; // Line to show flipper angle

private:	
	sf::Rect<float> m_testBoxRect;

	const float m_flipperDegree = { (0.0f + 180.0f) * (M_PI / 180.0f) }; // Used to show flipper angle
	sf::Vector2f m_flipperDir = { sin(m_flipperDegree), cos(m_flipperDegree) };// Used to show flipper angle
};

