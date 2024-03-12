/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>

#include "Game.h"
#include <iostream>
#include <cmath>


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
sf::Vector2f Game::v2fGetNormal(sf::Vector2f velocity)
{
	float length = v2fGetMagnitude(velocity);
	if (length != 0)
		return sf::Vector2f(velocity.x / length, velocity.y / length);
	else
		return velocity;
}
float Game::v2fGetMagnitude(sf::Vector2f velocity)
{
	float length = sqrt(v2fGetMagSquared(velocity));
	return length;
}
float Game::v2fGetMagSquared(sf::Vector2f velocity)
{
	return (velocity.x * velocity.x) + (velocity.y * velocity.y);
}

sf::Vector2f Game::v2fClamp(float max, float min, sf::Vector2f v2f)
{
	v2f.x = v2f.x > max ? max : v2f.x;
	v2f.x = v2f.x < min ? min : v2f.x;
	v2f.y = v2f.y > max ? max : v2f.y;
	v2f.y = v2f.y < min ? min : v2f.y;
	return v2f;
}

float Game::floatLerp(float a, float b, float t)
{
	return a + t * (b - a);
}

sf::Vector2f Game::v2fLerp(sf::Vector2f a, sf::Vector2f b, float t)
{
	return sf::Vector2f(floatLerp(a.x, b.x, t), floatLerp(a.y, b.y, t));
}

sf::Vector2f Game::v2fAbsolute(sf::Vector2f vector)
{
	float x = std::abs(vector.x);
	float y = std::abs(vector.y);
	return sf::Vector2f(x, y);
}

//float Game::v2fCrossProduct(sf::Vector2f a, sf::Vector2f b)
//{	// ? = sin-1 [ |a x b| / (|a| |b|) ].
//	return asin ((v2fGetMagnitude(a * b)) / ())
//}

float Game::v2fDotProduct(sf::Vector2f lhs, sf::Vector2f rhs)
{
	// return v2fGetMagnitude(lhs) * v2fGetMagnitude(rhs) * cos(v2fCrossProduct(lhs,rhs));
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

sf::Vector2f Game::v2fReflect(sf::Vector2f approach, sf::Vector2f normal)
{
	return approach - 2 * v2fDotProduct(approach, normal) * normal;
}

int Game::randomRange(int from, int to)
{
	int orderedFrom		= 0;
	int orderedTo		= 0;

	if (from > to)
	{
		orderedTo = from;
		orderedFrom = to;
	}
	else
	{
		orderedFrom = from;
		orderedTo = to;
	}

	int randomNumber	= rand() % abs(orderedTo - orderedFrom) + orderedFrom;
	return randomNumber;
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
	if (sf::Keyboard::K == t_event.key.code)
	{
		kick();
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
		m_balls[0].addForce(v2fGetNormal(displacement), v2fGetMagnitude(displacement));
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
	collision();
	screenSettle(t_deltaTime);
}

void Game::collision()
{
	sf::Vector2f normalisedDir = v2fGetNormal(m_balls[0].getVelocity());
	sf::Vector2f leadingPointOfBall = (normalisedDir * m_balls[0].M_RADIUS);
	leadingPointOfBall = leadingPointOfBall + m_balls[0].getPositionCur();

	if (m_testBoxRect.contains(leadingPointOfBall))
	{
		m_testBox.setFillColor(sf::Color::Green);

		if (m_balls[0].getPositionCur().x < m_testBox.getGlobalBounds().left)
		{
			m_balls[0].bounceCardinal(true);
		}
		else if (m_balls[0].getPositionCur().x > m_testBox.getGlobalBounds().left + m_testBox.getGlobalBounds().width)
		{
			m_balls[0].bounceCardinal(true);
		}
		else if (m_balls[0].getPositionCur().y < m_testBox.getGlobalBounds().top)
		{
			m_balls[0].bounceCardinal(false);
		}
		else
		{
			m_balls[0].bounceCardinal(false);
		}
		kick();
		 //sf::Vector2i newWindowPos = m_window.getPosition() + sf::Vector2i(0, 30);
		 //m_window.setPosition(newWindowPos);
	}
	else
	{
		m_testBox.setFillColor(sf::Color::Yellow);
	}

	float bumperColDist = v2fGetMagnitude(m_balls[0].getPositionCur() - m_bumper01.getPosition());
	
	if (bumperColDist < m_bumper01.getRadius() + m_balls[0].M_RADIUS)
	{
		m_bumper01.setFillColor(sf::Color::Blue);

		sf::Vector2f bumperNormal = v2fGetNormal(m_bumper01.getPosition() - m_balls[0].getPositionCur());
		
		sf::Vector2f reflectionVec = v2fReflect(normalisedDir, bumperNormal);

		m_balls[0].redirect(reflectionVec);

		kick();
	}
	else
	{
		m_bumper01.setFillColor(sf::Color::Cyan);
	}

}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(m_roundedTopBot);
	m_window.draw(m_backgroundImage);

	m_window.draw(m_testBox);
	m_window.draw(m_bumper01);
	
	
	m_window.draw(m_balls[0].m_ballShape);

	m_window.draw(m_ScoreBoard);

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

void Game::setupTable()
{
	m_backgroundImage.setOutlineColor(sf::Color::Magenta);
	m_backgroundImage.setFillColor(sf::Color::Transparent);
	m_backgroundImage.setOutlineThickness(m_backgroundImageThickness);
	m_backgroundImage.setSize(sf::Vector2f(WIDTH, HEIGHT));
	m_backgroundImage.setOrigin(sf::Vector2f(WIDTH * 0.5f, HEIGHT * 0.5f));
	m_backgroundImage.setPosition(sf::Vector2f(WIDTH * 0.5f, HEIGHT * 0.5f));

	m_view.setCenter(WIDTH * 0.5f, HEIGHT * 0.5f);
	m_viewCenterAtStart = m_view.getCenter();
	m_view.reset(sf::FloatRect(0.0f, 0.0f, WIDTH, HEIGHT));

	m_window.setView(m_view);
}

void Game::setupCollision()
{
	m_testBox.setOrigin(100.0f, 100.0f);
	m_testBox.setFillColor(sf::Color::Yellow);
	m_testBox.setSize(sf::Vector2f(200.0f, 200.0f));
	m_testBox.setPosition(WIDTH * 0.5f, HEIGHT * 0.75f);

	m_testBoxRect = sf::Rect<float>{ sf::Vector2f((WIDTH * 0.5f)-100.0f, (HEIGHT * 0.75f)-100.0f), m_testBox.getSize()};

	m_bumper01.setRadius(48.0f);
	m_bumper01.setOrigin(m_bumper01.getRadius(), m_bumper01.getRadius());
	m_bumper01.setFillColor(sf::Color::Cyan);
	m_bumper01.setOutlineColor(sf::Color::Red);
	m_bumper01.setOutlineThickness(-4.0f);
	m_bumper01.setPosition(WIDTH * 0.5f - m_bumper01.getRadius() * 0.5f, HEIGHT * 0.25f);

	m_roundedTopBot.setRadius(512.0f-32.0f);
	m_roundedTopBot.setOrigin(m_roundedTopBot.getRadius(), m_roundedTopBot.getRadius());
	m_roundedTopBot.setOutlineColor(sf::Color::Magenta);
	m_roundedTopBot.setOutlineThickness(100.0f);
	m_roundedTopBot.setPosition(WIDTH * 0.5f, HEIGHT * 0.5f);
}

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

void Game::kick()
{
	float moveRandom = static_cast<float>(randomRange(8, -8));
	m_view.move(sf::Vector2f(moveRandom, moveRandom));
	float rotRandom = static_cast<float>(randomRange(-10, 10));
	m_view.rotate(rotRandom);
	float zoomRandom = static_cast<float>(randomRange(-1, 1));
	m_view.zoom(zoomRandom);
	m_window.setView(m_view);

	m_pinballAudio.m_sndRattle.play();

	std::cout << "Random number is " << randomRange(-50, 50) << "\n";
}

bool Game::screenSettle(sf::Time t_deltaTime)
{
	if (m_view.getCenter() == sf::Vector2f(WIDTH * 0.5f, HEIGHT * 0.5f) && m_view.getRotation() == 0.0f && m_view.getSize() == sf::Vector2f(WIDTH, HEIGHT))
	{
		return true;
	}
	else
	{
		m_view.setCenter(v2fLerp(m_view.getCenter(), sf::Vector2f(WIDTH * 0.5f, HEIGHT * 0.5f), t_deltaTime.asSeconds() * m_viewReturnSpeed));
		m_view.setRotation(floatLerp(m_view.getRotation(), 0.0f, t_deltaTime.asSeconds() * m_viewReturnSpeed));
		m_view.setSize(v2fLerp(m_view.getSize(), sf::Vector2f(WIDTH, HEIGHT), t_deltaTime.asSeconds() * m_viewReturnSpeed));

		m_window.setView(m_view);
		return false;
	}	
}



void Game::updateScoreBoard()
{
	if (m_mouseCur.x >= 0 && m_mouseCur.x <= WIDTH && m_mouseCur.x >= 0 && m_mouseCur.y <= HEIGHT)
	{
		m_ScoreBoard.setString("Mouse X: " + std::to_string(m_mouseCur.x) +
			" | Mouse Y: " + std::to_string(m_mouseCur.y) +
			"\nBall X: " + std::to_string(m_balls[0].m_positionNxt.x) +
			" | Ball Y: " + std::to_string(m_balls[0].m_positionNxt.y));
	}
}

sf::Vector2f Game::testPos(sf::Vector2f t_pos)
{
	float wide = static_cast<float>(WIDTH);
	float high = static_cast<float>(HEIGHT);
	
	if (t_pos.x - m_balls[0].M_RADIUS <= 0.0f)
	{
		m_balls[0].bounceCardinal(true);
		kick();
	}

	if (t_pos.x + m_balls[0].M_RADIUS >= wide)
	{
		m_balls[0].bounceCardinal(true);
		kick();
	}
		
	if (t_pos.y - m_balls[0].M_RADIUS <= 0.0f)
	{
		m_balls[0].bounceCardinal(false);
		kick();
	}
		
	if (t_pos.y + m_balls[0].M_RADIUS >= high)
	{
		m_balls[0].bounceCardinal(false);
		kick();
	}
	return t_pos;
}


