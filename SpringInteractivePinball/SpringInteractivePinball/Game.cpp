/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>

#include "Game.h"
#include "Hlp.h"
#include "Globals.h"
#include "Collision.h"
#include <iostream>
#include <cmath>
#include <algorithm>

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
	srand(time(nullptr));

	m_pinballAudio.m_musArcadeAmbience01.setLoop(true);
	m_pinballAudio.m_musArcadeAmbience01.setVolume(60);
	m_pinballAudio.m_musArcadeAmbience01.play();
	m_pinballAudio.m_musHardRock.setLoop(true);
	m_pinballAudio.m_musHardRock.setVolume(20);
	m_pinballAudio.m_musHardRock.play();

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
		mouseScreenPosition(newEvent);

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
	if (sf::Keyboard::K == t_event.key.code)
	{
		tableKick(0.1f);
	}
}

void Game::processMouseDown(sf::Event t_event)
{
	m_mouseDown.x = static_cast<float>(t_event.mouseButton.x);
	m_mouseDown.y = static_cast<float>(t_event.mouseButton.y);
}

void Game::processMouseUp(sf::Event t_event)
{
	m_mouseUp.x = static_cast<float>(t_event.mouseButton.x);
	m_mouseUp.y = static_cast<float>(t_event.mouseButton.y);
		
	sf::Vector2f displacement; // Remember to ask about the word 'displacement'.

	displacement = (m_mouseDown - m_mouseUp) * m_nudgeScalar;
	
	std::cout << displacement.x << "-" << displacement.y << "\n";

	/*float headingD;
	float headingR;	
	headingR = std::atan2f(displacement.y, displacement.x);
	headingD = headingR * 180.0f / M_PI;
	headingD = headingD + 90.0f;*/

	if (sf::Mouse::Left == t_event.mouseButton.button)
	{
		// m_bigPlaneVelocity = displacement / 100.0f;
		m_balls[0].addForce(Hlp::v2fGetNormal(displacement), Hlp::v2fGetMagnitude(displacement));
		// m_bigHeading = headingD;
		// m_bigPlaneSprite.setRotation(headingD);
	}
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

	m_balls[0].move(t_deltaTime);
	m_balls[0].setPosition(testPos(m_balls[0].m_positionNxt));

	updateScoreBoard();
	m_col.collision();
	screenSettle(t_deltaTime);
}

//void Game::collision()
//{
//	
//}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_floorImage);
	m_window.draw(m_roundedTopBot);
	
	m_window.draw(m_backgroundImage);

	m_window.draw(m_testBox);
	m_window.draw(m_bumper01);
	m_window.draw(m_flipperTest);
	m_window.draw(m_flipperLine);
	m_window.draw(m_mouseLine);
	m_window.draw(m_mouseLineReflect);
	
	m_window.draw(m_balls[0].m_ballShape);

	m_window.draw(m_scoreBoard);

	m_window.display();
}

void Game::setup()
{
	setupFontAndText(); // load font 
	setupScoreBoard();
	setupTable();
	setupSprite(); // load texture
	setupCollision();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_karnivorDigitFont.loadFromFile("ASSETS\\FONTS\\KARNIVOD.ttf"))
	{
		std::cout << "problem loading Karnivod font" << std::endl;
	}
}

void Game::setupScoreBoard()
{
	m_scoreBoard.setFont(m_karnivorDigitFont);
	m_scoreBoard.setString("Hello World! I need 30 chars here.");
	m_scoreBoard.setCharacterSize(28);
	m_scoreBoard.setFillColor(sf::Color(255,191,0,255));
	m_scoreBoard.setOutlineColor(sf::Color::Black);
	m_scoreBoard.setOutlineThickness(8.0f);
	m_scoreBoard.setPosition((Globals::WIDTH * 0.5f) - (m_scoreBoard.getLocalBounds().width * 0.5f), m_scoreBoard.getLocalBounds().height);
}

void Game::setupTable()
{
	m_backgroundImage.setOutlineColor(sf::Color::Magenta);
	m_backgroundImage.setFillColor(sf::Color::White);
	m_backgroundImage.setOutlineThickness(m_backgroundImageThickness);
	m_backgroundImage.setSize(sf::Vector2f(Globals::WIDTH, HEIGHT));
	m_backgroundImage.setOrigin(sf::Vector2f(WIDTH * 0.5f, HEIGHT * 0.5f));
	m_backgroundImage.setPosition(sf::Vector2f(WIDTH * 0.5f, HEIGHT * 0.5f));

	m_floorImage.setFillColor(sf::Color::Black);
	m_floorImage.setSize(sf::Vector2f(WIDTH * 2.0f, HEIGHT * 2.0f));
	m_floorImage.setOrigin(sf::Vector2f(WIDTH, HEIGHT));
	m_floorImage.setPosition(sf::Vector2f(WIDTH, HEIGHT));

	m_view.setCenter(WIDTH * 0.5f, HEIGHT * 0.5f);
	m_viewCenterAtStart = m_view.getCenter();
	m_view.reset(sf::FloatRect(0.0f, 0.0f, WIDTH, HEIGHT));

	m_window.setView(m_view);
}

//void Game::setupCollision()
//{
//	
//}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{

}

void Game::mouseScreenPosition(sf::Event t_event)
{
	m_mouseCur.x = t_event.mouseMove.x;
	m_mouseCur.y = t_event.mouseMove.y;
		
}

void Game::tableKick(float scalar)
{
	float moveRandom = static_cast<float>(Hlp::randomRange(4.0f, -4.0f) * scalar);
	m_view.move(sf::Vector2f(moveRandom, moveRandom));
	float rotRandom = static_cast<float>(Hlp::randomRange(-0.125f, 0.125f) * scalar);
	m_view.rotate(rotRandom);
	float zoomRandom = static_cast<float>(Hlp::randomRange(-0.125f, 0.125f) * scalar);
	m_view.zoom(zoomRandom);
	m_window.setView(m_view);

	m_pinballAudio.m_sndRattle.play();

	std::cout << "Random number is " << Hlp::randomRange(-50.0f, 50.0f) << "\n";
}

bool Game::screenSettle(sf::Time t_deltaTime)
{
	if (m_view.getCenter() == sf::Vector2f(WIDTH * 0.5f, HEIGHT * 0.5f) && m_view.getRotation() == 0.0f && m_view.getSize() == sf::Vector2f(WIDTH, HEIGHT))
	{
		return true;
	}
	else
	{
		m_view.setCenter(Hlp::v2fLerp(m_view.getCenter(), sf::Vector2f(WIDTH * 0.5f, HEIGHT * 0.5f), t_deltaTime.asSeconds() * m_viewReturnSpeed));
		m_view.setRotation(Hlp::floatLerp(m_view.getRotation(), 0.0f, t_deltaTime.asSeconds() * m_viewReturnSpeed));
		m_view.setSize(Hlp::v2fLerp(m_view.getSize(), sf::Vector2f(WIDTH, HEIGHT), t_deltaTime.asSeconds() * m_viewReturnSpeed));

		m_window.setView(m_view);
		return false;
	}	
}

void Game::updateScoreBoard()
{
	if (m_mouseCur.x >= 0 && m_mouseCur.x <= WIDTH && m_mouseCur.x >= 0 && m_mouseCur.y <= HEIGHT)
	{
		m_scoreBoard.setString("Mouse X: " + std::to_string(m_mouseCur.x) +
			" | Mouse Y: " + std::to_string(m_mouseCur.y) +
			"\nBall X: " + std::to_string(static_cast<int>(m_balls[0].m_positionNxt.x)) +
			" | Ball Y: " + std::to_string(static_cast<int>(m_balls[0].m_positionNxt.y)) +
			"\nMouseVec: " + std::to_string(m_testVec02.x) + " | " + std::to_string(m_testVec02.y));
	}
}

sf::Vector2f Game::testPos(sf::Vector2f t_pos)
{
	float wide = static_cast<float>(WIDTH);
	float high = static_cast<float>(HEIGHT);
	
	if (t_pos.x - m_balls[0].M_RADIUS <= 0.0f)
	{
		m_balls[0].bounceCardinal(true);
		tableKick(0.1f);
	}

	if (t_pos.x + m_balls[0].M_RADIUS >= wide)
	{
		m_balls[0].bounceCardinal(true);
		tableKick(0.1f);
	}
		
	if (t_pos.y - m_balls[0].M_RADIUS <= 0.0f)
	{
		m_balls[0].bounceCardinal(false);
		tableKick(0.1f);
	}
		
	if (t_pos.y + m_balls[0].M_RADIUS >= high)
	{
		m_balls[0].bounceCardinal(false);
		tableKick(0.1f);
	}
	return t_pos;
}