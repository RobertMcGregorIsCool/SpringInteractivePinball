/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>
#pragma once

#include <SFML/Graphics.hpp>

#include "PinballAud.h"
#include "Collision.h"

class Render
{
public:

	Render(sf::RenderWindow& t_window, Collision& t_col);
	~Render();

	void render(Ball t_balls[4], sf::Text t_scoreBoard);

	sf::RenderWindow& m_window; // main SFML window
	Collision& m_collision;
	sf::View m_view; // View onto table
	sf::Vector2f m_viewCenterAtStart;

	sf::RectangleShape m_floorImage;
	sf::RectangleShape m_backgroundImage; // backgroundImage
	float m_backgroundImageThickness = -8.0f;

	void tableKick(float scalar = 1.0f);
	bool screenSettle(sf::Time t_deltaTime);

private:
	
	
	// PinballAud m_pinballAudio;

	float m_viewReturnSpeed = 32.0f;
};

