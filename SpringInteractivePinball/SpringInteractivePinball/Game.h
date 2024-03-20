/// <summary>
/// author Robert McGregor login: c00302210
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "Ball.h"
#include "Collision.h"
#include "Render.h"
#include "PinballAud.h"
#include <cstdlib>

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

	void updateScoreBoard();

	const float m_nudgeScalar = 0.5f;

	Collision m_collision;

	sf::RenderWindow m_window; // main SFML window
	Render m_render{ m_window, m_collision };

	// sf::Font m_ArialBlackfont; // font used by message
	sf::Font m_karnivorDigitFont; // font used by message
	sf::Text m_scoreBoard;

	sf::Vector2i m_mouseCur;

	sf::Vector2f m_mouseDown;//location of mouse down click
	sf::Vector2f m_mouseUp; // Reluctantly have to use this, boo.

	bool m_screenKicked = false;
	
	static constexpr int M_MAX_BALLS{ 4 };
	int m_ballsCurAmount = 1;
	Ball m_balls[M_MAX_BALLS];

	//float m_flipperTestPos = 0.0f;
	
	PinballAud m_pinballAudio;

	bool m_exitGame; // control exiting game

	
};
#endif // !GAME_HPP

