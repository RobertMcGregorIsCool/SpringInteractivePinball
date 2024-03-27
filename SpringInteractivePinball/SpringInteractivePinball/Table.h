/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>

#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Flipper.h"
#include "Bumper.h"
class Table
{
	sf::Color m_darkGrey {100, 100, 100, 255};
	sf::Color m_veryDarkGrey {25, 25, 25, 255};
	sf::Color m_ligtGrey {200, 200, 200, 255};


public:

	Table();
	~Table();

	sf::RectangleShape m_gutterWallLeft;
	sf::Rect<float> m_gutterWallLeftRect;

	sf::RectangleShape m_gutterWallRigt;
	sf::Rect<float> m_gutterWallRigtRect;
	
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

	sf::CircleShape m_roundedTopBot;

	Flipper m_flipRigt{ false, 90.0f, sf::Vector2f(360.0f, 875.0f), 
		240.0f, 260.0f, 300.0f, m_roundedTopBot };

	Flipper m_flipLeft{ true, 90.0f, sf::Vector2f(140.0f, 875.0f), 
		120.0f, 100.0f, 60.0f, m_roundedTopBot };

	Flipper m_flipLeftHigh { true, 90.0f, sf::Vector2f(10.0f, 180.0f),
		120.0f +60.0f, 100.0f +60.0f, 60.0f +60.0f, m_roundedTopBot };

	Bumper m_bump01 { 48.0f, m_darkGrey, m_veryDarkGrey, m_ligtGrey, -4.0f, sf::Vector2f(450.0f, 250.0f) };
	Bumper m_bump02{ 48.0f, m_darkGrey, m_veryDarkGrey, m_ligtGrey, -4.0f, sf::Vector2f(160.0f, 650.0f) };
	Bumper m_bump03{ 48.0f, m_darkGrey, m_veryDarkGrey, m_ligtGrey, -4.0f, sf::Vector2f(330.0, 590.0f) };
	Bumper m_bump04{ 48.0f, m_darkGrey, m_veryDarkGrey, m_ligtGrey, -4.0f, sf::Vector2f(245.0f, 410.0f) };
	Bumper m_bump05{ 48.0f, m_darkGrey, m_veryDarkGrey, m_ligtGrey, -4.0f, sf::Vector2f(175.0f, 270.0f) };
};

