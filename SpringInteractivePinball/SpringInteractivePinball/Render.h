#pragma once

#include <SFML/Graphics.hpp>

#include "PinballAud.h"
//#include "Collision.h"

class Render
{
public:

	Render(sf::RenderWindow& t_window);
	~Render();

	void render(Ball t_balls[4], sf::Text t_scoreBoard);

	sf::RenderWindow& m_window; // main SFML window
	sf::View m_view; // View onto table
	sf::Vector2f m_viewCenterAtStart;

	sf::RectangleShape m_floorImage;
	sf::RectangleShape m_backgroundImage; // backgroundImage
	float m_backgroundImageThickness = -8.0f;

	void tableKick(float scalar = 1.0f);
	bool screenSettle(sf::Time t_deltaTime);

private:
	
	Collision m_col;
	PinballAud m_pinballAudio;

	float m_viewReturnSpeed = 32.0f;
};

