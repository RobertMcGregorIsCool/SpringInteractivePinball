/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>

#include "Game.h"
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

float Game::v2fCrossProduct(sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.y - a.y * b.x;
}

float Game::v2fDotProduct(sf::Vector2f lhs, sf::Vector2f rhs)
{
	// return v2fGetMagnitude(lhs) * v2fGetMagnitude(rhs) * cos(v2fCrossProduct(lhs,rhs));
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

sf::Vector2f Game::v2fReflect(sf::Vector2f approach, sf::Vector2f normal)
{
	return approach - 2 * v2fDotProduct(approach, normal) * normal;
}

sf::Vector2f Game::v2fPerpendicularClockwise(sf::Vector2f vec)
{
	return sf::Vector2f(vec.y, -vec.x);
}

sf::Vector2f Game::v2fPerpendicularAntiClockwise(sf::Vector2f vec)
{
	return sf::Vector2f(-vec.y, vec.x);
}

int Game::randomRange(int from, int to)
{
	int orderedFrom	= std::min(from,to);
	int orderedTo	= std::max(to,from);

	int randomNumber	= rand() % abs(orderedTo - orderedFrom) + orderedFrom;
	return randomNumber;
}

float Game::randomRange(float from, float to)
{
	from *= 100.0f;
	to *= 100.0f;
	
	float output = static_cast<float>(randomRange(static_cast<int>(from), static_cast<int>(to)));

	return output * 0.01f;
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
		tableKick();
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
		tableKick();
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

		tableKick();
	}
	else
	{
		m_bumper01.setFillColor(sf::Color::Cyan);
	}

	sf::Vector2f m_mouseCurFloat = sf::Vector2f(static_cast<float>(m_mouseCur.x), static_cast<float>(m_mouseCur.y));
	if (v2fGetMagnitude(m_flipperTest.getPosition() - m_balls[0].getPositionCur()) < m_flipperTest.getRadius())
	{
		//m_testVec01 = v2fGetNormal(m_flipperTest.getPosition() + (m_flipperDir * m_flipperTest.getRadius()));
		m_testVec02 = v2fGetNormal(m_balls[0].getPositionCur() - m_flipperTest.getPosition());
		// m_flipperTestPos = v2fDotProduct(m_testVec01, m_testVec02)

		sf::Vector2f straightUp {0.0f, 1.0f};
		float flipperAngleR = atan2(v2fCrossProduct(straightUp, m_testVec02), v2fDotProduct(straightUp, m_testVec02));
		float flipperAngleD = flipperAngleR * 180.0f / M_PI;
		flipperAngleD += 180.0f;
		std::cout << "The angle is " << flipperAngleD << ".\n\n";

		m_flipperTest.setFillColor(sf::Color::Cyan);

		//if (m_flipperTestPos < -0.1f && m_flipperTestPos > -0.9f)
		if(flipperAngleD < 300.0f && flipperAngleD > 240.0f)
		{
			//std::cout << "Cursor inside circle!";
			m_flipperTest.setFillColor(sf::Color::Green);
		}
	}
	else
	{
		//std::cout << "Cursor outside circle!";
		m_flipperTest.setFillColor(sf::Color(220, 220, 220, 255));
	}
	
	

	sf::Vertex point;
	point.color = sf::Color::Red;
	m_mouseLine.clear();
	point.position = m_flipperTest.getPosition();
	m_mouseLine.append(point);
	point.position = m_mouseCurFloat;
	m_mouseLine.append(point);

	point.color = sf::Color::Yellow;
	m_mouseLineReflect.clear();
	point.position = m_mouseCurFloat;
	m_mouseLineReflect.append(point);
	sf::Vector2f lineBounce = m_flipperTest.getPosition() - m_mouseCurFloat;
	lineBounce = v2fPerpendicularClockwise(lineBounce);

	point.position = m_mouseCurFloat + lineBounce;
	m_mouseLineReflect.append(point);
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

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
	m_scoreBoard.setPosition((WIDTH * 0.5f) - (m_scoreBoard.getLocalBounds().width * 0.5f), m_scoreBoard.getLocalBounds().height);
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
	m_bumper01.setPosition(WIDTH * 0.5f, HEIGHT * 0.25f); // -m_bumper01.getRadius() * 0.5f, HEIGHT * 0.25f);

	m_roundedTopBot.setRadius(512.0f-32.0f);
	m_roundedTopBot.setOrigin(m_roundedTopBot.getRadius(), m_roundedTopBot.getRadius());
	m_roundedTopBot.setOutlineColor(sf::Color::Magenta);
	m_roundedTopBot.setOutlineThickness(100.0f);
	m_roundedTopBot.setPosition(WIDTH * 0.5f, HEIGHT * 0.5f);

	m_flipperTest.setRadius(80.0f);
	m_flipperTest.setOrigin(m_flipperTest.getRadius(), m_flipperTest.getRadius());
	m_flipperTest.setFillColor(sf::Color(220, 220, 220, 255));
	m_flipperTest.setOutlineColor(sf::Color::Black);
	m_flipperTest.setOutlineThickness(1.0f);
	m_flipperTest.setPosition(WIDTH * 0.5f, HEIGHT * 0.43f);

	sf::Vertex point;
	point.color = sf::Color::Blue;
	m_flipperLine.clear();
	point.position = m_flipperTest.getPosition();
	m_flipperLine.append(point);
	point.position = m_flipperTest.getPosition() + (m_flipperDir * m_flipperTest.getRadius());
	m_flipperLine.append(point);
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

void Game::tableKick()
{
	float moveRandom = static_cast<float>(randomRange(4.0f, -4.0f));
	m_view.move(sf::Vector2f(moveRandom, moveRandom));
	float rotRandom = static_cast<float>(randomRange(-0.125f, 0.125f));
	m_view.rotate(rotRandom);
	float zoomRandom = static_cast<float>(randomRange(-0.125f, 0.125f));
	m_view.zoom(zoomRandom);
	m_window.setView(m_view);

	m_pinballAudio.m_sndRattle.play();

	std::cout << "Random number is " << randomRange(-50.0f, 50.0f) << "\n";
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
		m_scoreBoard.setString("Mouse X: " + std::to_string(m_mouseCur.x) +
			" | Mouse Y: " + std::to_string(m_mouseCur.y) +
			"\nBall X: " + std::to_string(static_cast<int>(m_balls[0].m_positionNxt.x)) +
			" | Ball Y: " + std::to_string(static_cast<int>(m_balls[0].m_positionNxt.y)) +
			"\nMouseVector is: " + std::to_string(m_testVec02.x) + " | " + std::to_string(m_testVec02.y));
	}
}

sf::Vector2f Game::testPos(sf::Vector2f t_pos)
{
	float wide = static_cast<float>(WIDTH);
	float high = static_cast<float>(HEIGHT);
	
	if (t_pos.x - m_balls[0].M_RADIUS <= 0.0f)
	{
		m_balls[0].bounceCardinal(true);
		tableKick();
	}

	if (t_pos.x + m_balls[0].M_RADIUS >= wide)
	{
		m_balls[0].bounceCardinal(true);
		tableKick();
	}
		
	if (t_pos.y - m_balls[0].M_RADIUS <= 0.0f)
	{
		m_balls[0].bounceCardinal(false);
		tableKick();
	}
		
	if (t_pos.y + m_balls[0].M_RADIUS >= high)
	{
		m_balls[0].bounceCardinal(false);
		tableKick();
	}
	return t_pos;
}


