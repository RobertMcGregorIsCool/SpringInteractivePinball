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
	void setup();
	void setupFontAndText();
	void setupScoreBoard();
	void setupSprite();
	
	void render();

	void update(sf::Time t_deltaTime);

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseUp(sf::Event t_event);	

	void mouseScreenPosition(sf::Event t_event);

	const unsigned int WIDTH = 600U;
	const unsigned int HEIGHT = 1016U;

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_ScoreBoard;

	int m_mouseXCur = 0;
	int m_mouseYCur = 0;

	sf::Vector2f m_mouseDown;//location of mouse down click

	Ball balls[4] = {	Ball(16.0f, sf::Vector2f(300.0f, 500.0f)),
						Ball(16.0f, sf::Vector2f(300.0f, 500.0f)),
						Ball(16.0f, sf::Vector2f(300.0f, 500.0f)),
						Ball(16.0f, sf::Vector2f(300.0f, 500.0f))};
	bool m_exitGame; // control exiting game

};

#endif // !GAME_HPP

