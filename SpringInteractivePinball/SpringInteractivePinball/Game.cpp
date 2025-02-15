/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
/// https://playold.games/play-game/pinball-fantasies/play/ - Party Land is 320x576
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
	m_window{ sf::VideoMode{ Globals::WIDTH, Globals::HEIGHT, 32U }, "Spring Interactive Pinball!" },
	m_exitGame{false} //when true game will exit
{
	setup();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game(){}
/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	// m_globals.m_timeScalar = 1.0f;
	srand(time(nullptr));

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
			update(timePerFrame* m_globals.m_timeScalar); //60 fps
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
		m_mouseCur.x = newEvent.mouseMove.x;
		m_mouseCur.y = newEvent.mouseMove.y;

		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeysDn(newEvent);
		}
		if (sf::Event::KeyReleased == newEvent.type) // user released a key
		{
			processKeysUp(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMouseDown(newEvent);
		}
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseUp(newEvent);
		}
		if (sf::Event::MouseWheelScrolled == newEvent.type)
		{
			processMouseScroll(newEvent);
		}
	}
}

/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeysDn(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::K == t_event.key.code)
	{
		m_render.m_kickTest = true;
	}
	
	if ((sf::Keyboard::LShift == t_event.key.code || sf::Keyboard::Left == t_event.key.code) && !m_cmds.m_pressedLeftFlip)
	{
		m_cmds.leftFlipDn();
	}
	if ((sf::Keyboard::RShift == t_event.key.code || sf::Keyboard::Right == t_event.key.code) && !m_cmds.m_pressedRigtFlip)
	{
		m_cmds.rigtFlipDn();
	}
	if ((sf::Keyboard::Up == t_event.key.code && !m_cmds.m_pressedLaunch))
	{
		m_cmds.launchDn();
	}
	if (sf::Keyboard::Space == t_event.key.code && !m_cmds.m_pressedNudge)
	{
		m_cmds.m_pressedNudge = true;
		m_render.tableKick();
		for (int i = 0; i < m_ballsCurAmount; i++)
		{
			m_cmds.nudgeDn(m_balls[i]);
		}
	}
	if (sf::Keyboard::Down== t_event.key.code && !m_cmds.m_pressedLaunch)
	{
		m_cmds.launchDn();
	}
	if (sf::Keyboard::Return == t_event.key.code)
	{
		m_cmds.newBall();
	}
	if (sf::Keyboard::T == t_event.key.code)
	{
		for (int i = 0; i < m_ballsCurAmount; i++)
		{
			m_cmds.teleportBall(m_balls[i], sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(m_window).x), static_cast<float>(sf::Mouse::getPosition(m_window).y)));
		}
	}
}

/// <summary>
/// Deal with user releasing keys
/// </summary>
/// <param name="t_event">Current event</param>
void Game::processKeysUp(sf::Event t_event)
{
	if ((sf::Keyboard::LShift == t_event.key.code || sf::Keyboard::Left == t_event.key.code) && m_cmds.m_pressedLeftFlip)
	{
		m_render.tableKick();
		m_cmds.leftFlipUp();
	}
	if ((sf::Keyboard::RShift == t_event.key.code || sf::Keyboard::Right == t_event.key.code) && m_cmds.m_pressedRigtFlip)
	{
		m_render.tableKick();
		m_cmds.rigtFlipUp();
	}
	if (sf::Keyboard::Space == t_event.key.code)
	{
		m_cmds.m_pressedNudge = false;
	}
	if (sf::Keyboard::Down == t_event.key.code && m_cmds.m_pressedLaunch)
	{
		m_cmds.launchUp(m_balls);
	}

	if (sf::Keyboard::Hyphen == t_event.key.code)
	{
		m_globals.scaleTimeCheck(-0.05f);
	}

	if (sf::Keyboard::Equal == t_event.key.code)
	{
		m_globals.scaleTimeCheck(0.05f);
	}
}

/// <summary>
/// Deal with user pressing mouse button(s)
/// </summary>
/// <param name="t_event">Current event</param>
void Game::processMouseDown(sf::Event t_event)
{
	m_mouseDown.x = static_cast<float>(t_event.mouseButton.x);
	m_mouseDown.y = static_cast<float>(t_event.mouseButton.y);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!m_cmds.m_pressedLeftFlip)
		{
			m_cmds.leftFlipDn();
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (!m_cmds.m_pressedRigtFlip)
		{
			m_cmds.rigtFlipDn();
		}
	}
}

/// <summary>
/// Deal with user releasing mouse button(s)
/// </summary>
/// <param name="t_event">Current event</param>
void Game::processMouseUp(sf::Event t_event)
{
	m_mouseUp.x = static_cast<float>(t_event.mouseButton.x);
	m_mouseUp.y = static_cast<float>(t_event.mouseButton.y);
		
	sf::Vector2f displacement;

	displacement = (m_mouseDown - m_mouseUp) * M_NUDGE_SCALAR;
	
	std::cout << "Displacement is " << Hlp::v2fGetMagnitude(displacement) << ".\n\n";

	if (m_cmds.M_NUDGE_THRESHOLD < Hlp::v2fGetMagnitude(displacement))
	{
		m_render.tableKick();

		for (int i = 0; i < m_ballsCurAmount; i++)
		{
			m_balls[i].addForce(Hlp::v2fGetNormal(displacement), Hlp::v2fGetMagnitude(displacement));
		}
	}

	/// Bunch of this code originally derived from Pete's Aircrash, this here for reference
	/// float headingD;
	/// float headingR;	
	/// headingR = std::atan2f(displacement.y, displacement.x);
	/// headingD = headingR * 180.0f / M_PI;
	/// headingD = headingD + 90.0f;

	/// if (sf::Mouse::Left == t_event.mouseButton.button)
	/// {
	/// 	 m_bigPlaneVelocity = displacement / 100.0f;
	/// 	
	/// 	 m_bigHeading = headingD;
	/// 	 m_bigPlaneSprite.setRotation(headingD);
	/// }

	if (m_cmds.m_pressedLeftFlip)
	{
		m_cmds.leftFlipUp();
	}

	if (m_cmds.m_pressedRigtFlip)
	{
		m_cmds.rigtFlipUp();
	}
}

/// <summary>
/// Deal with user scrolling mouse wheel.
/// </summary>
/// <param name="t_event">Current event</param>
void Game::processMouseScroll(sf::Event t_event)
{
	if (t_event.mouseWheelScroll.delta > 0)
	{
		if (m_globals.debug)
		{
			m_collision.setLaunchBoxScalarFromCommand(m_cmds.m_launchTimer);
			m_cmds.m_launchTimer = 0.0f;
			m_cmds.launchUp(m_balls);
		}
		else
		{
			m_collision.setLaunchBoxScalarFromCommand(1.0f);
			m_cmds.launchUp(m_balls);
		}
	}
	else
	{
		if (m_globals.debug)
		{
			if (m_cmds.m_launchTimer < m_cmds.M_LAUNCH_PERIOD)
			{
				m_cmds.m_launchTimer += m_cmds.M_LAUNCH_WHEEL_INCREMENT;
			}
			else
			{
				m_cmds.m_launchTimer = m_cmds.M_LAUNCH_PERIOD;
			}
		}
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

	updateScoreBoard();
	
	for (int i = 0; i < m_ballsCurAmount; i++)
	{
		m_balls[i].update(t_deltaTime);
		m_collision.detect(m_balls[i], m_mouseCur);
		
		if (m_render.m_kickTest)
		{
			std::cout << "Trying to kick ball# " << i << "!\n\n";
			m_balls[i].setVelocity(sf::Vector2f(m_balls[i].getVelocity().x * -1, m_balls[i].getVelocity().y * -1));
			m_render.m_kickTest = false;
		}
		
		m_balls[i].setPosition(m_balls[i].m_positionNxt);
	}

	if (m_globals.debug)
	{
		m_render.visualDebugLines(m_mouseCur);
	}

	m_render.screenSettle(t_deltaTime);

	m_cmds.update(t_deltaTime);
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_render.render(m_balls, m_scoreBoard);
}

/// <summary>
/// Setup hud and general content - mostly unused as I don't have art assets
/// </summary>
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
	if (!m_karnivorDigitFont.loadFromFile("ASSETS\\FONTS\\KARNIVOD.ttf"))
	{
		std::cout << "problem loading Karnivod font" << std::endl;
	}
}

/// <summary>
/// Make scoreboard look nice and presentable
/// </summary>
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

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite() 
{
	// Really wish I had art assets to put in here.
}

/// <summary>
/// Update and display the scores or debug information
/// </summary>
void Game::updateScoreBoard()
{
	if (m_globals.debug)
	{
		if (m_mouseCur.x >= 0 && m_mouseCur.x <= Globals::WIDTH && m_mouseCur.x >= 0 && m_mouseCur.y <= Globals::HEIGHT)
		{
			m_scoreBoard.setString("Mouse X: " + std::to_string(m_mouseCur.x) +
				" | Mouse Y: " + std::to_string(m_mouseCur.y) +
				"\nBall X: " + std::to_string(static_cast<int>(m_balls[0].m_positionNxt.x)) +
				" | Ball Y: " + std::to_string(static_cast<int>(m_balls[0].m_positionNxt.y)) +
				"\nBall veloc: " + std::to_string(m_balls[0].getVelocity().x) + " | " + std::to_string(m_balls[0].getVelocity().y) +
				"\nMX: " + std::to_string(sf::Mouse::getPosition(m_window).x) + " | MY: " + std::to_string(sf::Mouse::getPosition(m_window).y) +
				"\nTime Scalar is: " + std::to_string(m_globals.m_timeScalar));
		}
	}
	else
	{
		m_scoreBoard.setString("SCORE: " + std::to_string(m_globals.m_score));
	}	
}

