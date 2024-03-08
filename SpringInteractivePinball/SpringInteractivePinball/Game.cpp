/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ WIDTH, HEIGHT, 32U }, "Spring Interactive Pinball!" },
	m_exitGame{false} //when true game will exit
{
	setup();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMouseDown(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseUp(newEvent);
		}
		mouseScreenPosition(newEvent);
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

void Game::processMouseDown(sf::Event t_event)
{
	std::cout << "Clicky!";

	m_mouseDown.x = static_cast<float>(t_event.mouseButton.x);
	m_mouseDown.y = static_cast<float>(t_event.mouseButton.y);
}

void Game::processMouseUp(sf::Event t_event)
{
	std::cout << "Unclicky!";

	sf::Vector2f mouseUp;
	sf::Vector2f displacement;
	float headingD;
	float headingR;

	mouseUp.x = static_cast<float>(t_event.mouseButton.x);
	mouseUp.y = static_cast<float>(t_event.mouseButton.y);

	displacement = mouseUp - m_mouseDown;
	headingR = std::atan2f(displacement.y, displacement.x);
	/*headingD = headingR * 180.0f / M_PI;
	headingD = headingD + 90.0f;

	if (sf::Mouse::Left == t_event.mouseButton.button)
	{
		m_bigHeading = headingD;
		m_bigPlaneVelocity = displacement / 100.0f;
		m_bigPlaneSprite.setRotation(headingD);
	}*/
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(m_ScoreBoard);

	m_window.draw(balls[0].ballShape);

	m_window.display();
}

void Game::setup()
{
	setupFontAndText(); // load font 
	setupScoreBoard();
	setupSprite(); // load texture
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
}

void Game::setupScoreBoard()
{
	m_ScoreBoard.setFont(m_ArialBlackfont);
	m_ScoreBoard.setString("Hello World! I need roughly 30 chars here.");
	m_ScoreBoard.setCharacterSize(24);
	m_ScoreBoard.setFillColor(sf::Color::Green);
	m_ScoreBoard.setOutlineColor(sf::Color::Black);
	m_ScoreBoard.setPosition((WIDTH * 0.5f) - (m_ScoreBoard.getLocalBounds().width * 0.5f), m_ScoreBoard.getLocalBounds().height);
}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{

}

void Game::mouseScreenPosition(sf::Event t_event)
{
	m_mouseXCur = t_event.mouseMove.x;
	m_mouseYCur = t_event.mouseMove.y;
	m_ScoreBoard.setString("Mouse X: " + std::to_string(m_mouseXCur) + " | Mouse Y: " + std::to_string(m_mouseYCur));
}
