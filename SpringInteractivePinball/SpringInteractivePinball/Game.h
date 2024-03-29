/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
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
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "Ball.h"
#include "Table.h"
#include "Collision.h"
#include "Render.h"
#include "PinballAud.h"
#include "Commands.h"
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
	void processKeysDn(sf::Event t_event);
	void processKeysUp(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseUp(sf::Event t_event);
	void processMouseScroll(sf::Event t_event);

	void updateScoreBoard();

	const float M_NUDGE_SCALAR = 4.0f;

	/// <summary>
	/// Instances of important classes!
	/// </summary>
	Globals m_globals;
	Table	m_table;
	PinballAud m_pinballAudio;
	sf::RenderWindow m_window; /// main SFML window
	Render m_render{ m_window, m_table, m_pinballAudio, m_globals};
	Collision m_collision{ m_table, m_render, m_globals};
	Commands m_cmds{ m_collision, m_table, m_globals };

	sf::Font m_karnivorDigitFont; /// font used by message
	sf::Text m_scoreBoard;

	sf::Vector2i m_mouseCur;

	sf::Vector2f m_mouseDown;	///location of mouse down click
	sf::Vector2f m_mouseUp;		/// Reluctantly have to use this, boo.

	bool m_screenKicked = false; /// Used to determine if the screen needs to be settled.
	
	static constexpr int M_MAX_BALLS{ 4 };
	int m_ballsCurAmount = 1;
	Ball m_balls[M_MAX_BALLS];

	bool m_exitGame; /// control exiting game	
};
#endif // !GAME_HPP