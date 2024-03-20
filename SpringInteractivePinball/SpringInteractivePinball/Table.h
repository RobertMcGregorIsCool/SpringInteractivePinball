/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>

#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"
class Table
{
public:

	Table();
	~Table();

	sf::RectangleShape m_testBox;

	sf::CircleShape m_roundedTopBot;

	sf::CircleShape m_bumper01;

	sf::CircleShape m_flipperTest;

	sf::Rect<float> m_testBoxRect;
};

