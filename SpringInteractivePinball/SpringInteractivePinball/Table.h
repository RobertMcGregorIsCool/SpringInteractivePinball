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

	sf::RectangleShape m_launchKicker;
	sf::Rect<float> m_launchKickerRect;

	sf::RectangleShape m_launchWall;
	sf::Rect<float> m_launchWallRect;

	sf::RectangleShape m_noCollideLaunch;
	sf::Rect<float>m_noCollideLaunchRect;

	sf::RectangleShape m_noCollideGutterA;
	sf::Rect<float>m_noCollideGutterARect;

	sf::RectangleShape m_gutterTeleport;
	sf::Rect<float>m_gutterTeleportRect;

	sf::CircleShape m_roundedTopBot;

	sf::CircleShape m_bumper01;

	sf::CircleShape m_flipperTest;
};

