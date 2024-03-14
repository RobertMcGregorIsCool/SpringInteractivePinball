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
#include "PinballAud.h"
#include <cstdlib>

#define _USE_MATH_DEFINES	// Ehh, why not.
#include <math.h>			// Go the whole hog. Be bigger than god.

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	sf::Vector2f testPos(sf::Vector2f t_pos);

private:
	void setup();
	void setupFontAndText();
	void setupScoreBoard();
	void setupTable();
	void setupCollision();
	void setupSprite();
	
	void render();

	void update(sf::Time t_deltaTime);

	void collision();

	void processEvents();
	void processKeys(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processMouseUp(sf::Event t_event);	

	void mouseScreenPosition(sf::Event t_event);

	void tableKick(float scalar = 1.0f);
	bool screenSettle(sf::Time t_deltaTime);

	void updateScoreBoard();

	static const unsigned int WIDTH = 600U;
	static const unsigned int HEIGHT = 960U;

	const float m_nudgeScalar = 0.5f;

	sf::RenderWindow m_window; // main SFML window
	sf::View m_view; // View onto table

	sf::RectangleShape m_floorImage;
	sf::RectangleShape m_backgroundImage; // backgroundImage
	float m_backgroundImageThickness = -8.0f;

	// sf::Font m_ArialBlackfont; // font used by message
	sf::Font m_karnivorDigitFont; // font used by message
	sf::Text m_scoreBoard;

	sf::Vector2i m_mouseCur;

	sf::Vector2f m_mouseDown;//location of mouse down click
	sf::Vector2f m_mouseUp; // Reluctantly have to use this, boo.

	bool m_screenKicked = false;
	sf::Vector2f m_viewCenterAtStart;
	float m_viewReturnSpeed = 32.0f;

	Ball m_balls[4];

	sf::RectangleShape m_testBox;
	sf::Rect<float> m_testBoxRect;

	sf::CircleShape m_bumper01;
	sf::CircleShape m_roundedTopBot;

	sf::CircleShape m_flipperTest;
	sf::VertexArray m_flipperLine{sf::Lines}; // Line to show flipper angle
	sf::VertexArray m_mouseLine {sf::Lines};
	sf::VertexArray m_mouseLineReflect {sf::Lines};
	//float m_flipperTestPos = 0.0f;
	//const float m_flipperDegree = { (0.0f + 180.0f) * (M_PI / 180.0f) };
	//sf::Vector2f m_flipperDir = { sin(m_flipperDegree), cos(m_flipperDegree) };
	//sf::Vector2f m_testVec01;
	sf::Vector2f m_testVec02;

	PinballAud m_pinballAudio;

	bool m_exitGame; // control exiting game
};
#endif // !GAME_HPP

