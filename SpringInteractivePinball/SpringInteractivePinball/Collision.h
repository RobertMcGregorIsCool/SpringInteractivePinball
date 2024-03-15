#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>

class Collision
{
public:
	Collision();
	~Collision();

	void setupCollision();
	void collision();

private:

	sf::RectangleShape m_testBox;
	sf::Rect<float> m_testBoxRect;
};

