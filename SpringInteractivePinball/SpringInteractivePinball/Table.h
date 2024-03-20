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
	sf::Rect<float> m_testBoxRect;
	
	sf::RectangleShape m_launchBox;
	sf::Rect<float> m_launchBoxRect;

	sf::RectangleShape m_launchWall;
	sf::Rect<float> m_launchWallRect;

	sf::CircleShape m_roundedTopBot;

	sf::CircleShape m_bumper01;

	sf::CircleShape m_flipperTest;
};

