/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Ball.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setup();
	void setupFontAndText();
	void setupSprite();

	const unsigned int WIDTH = 600U;
	const unsigned int HEIGHT = 1016U;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	Ball ball;
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

