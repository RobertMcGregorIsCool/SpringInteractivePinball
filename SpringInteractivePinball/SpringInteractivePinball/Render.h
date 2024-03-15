#pragma once

#include <SFML/Graphics.hpp>
#include "Collision.h"

class Render
{
public:

	Render();
	~Render();

	void render(sf::RenderWindow& t_window, Ball t_balls[4], );

	// sf::RenderWindow m_window; // main SFML window
	sf::View m_view; // View onto table

	sf::RectangleShape m_floorImage;
	sf::RectangleShape m_backgroundImage; // backgroundImage
	float m_backgroundImageThickness = -8.0f;

private:
	
	Collision m_col;

};

