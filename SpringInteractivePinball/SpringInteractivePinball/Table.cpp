/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>

#include "Table.h"

Table::Table()
{
	


	//m_testBox.setOrigin(100.0f, 100.0f);
	//m_testBox.setFillColor(sf::Color(26, 32, 39, 255)); // sf::Color::Yellow);
	//m_testBox.setSize(sf::Vector2f(200.0f, 200.0f));
	//m_testBox.setPosition(Globals::WIDTH * 0.5f, Globals::HEIGHT * 1.05f);
	//m_testBoxRect = m_testBox.getGlobalBounds();

	m_launchWall.setSize(sf::Vector2f(16.0f, 800.0f));
	m_launchWall.setOrigin(m_launchWall.getSize().x * 0.5f, m_launchWall.getSize().y);
	m_launchWall.setFillColor(sf::Color(26, 32, 39, 230));
	m_launchWall.setPosition(Globals::WIDTH * 0.91f, Globals::HEIGHT * 1.0f);
	m_launchWallRect = m_launchWall.getGlobalBounds();

	m_launchBox.setSize(sf::Vector2f(50.0f, 880.0f));
	m_launchBox.setOrigin(m_launchBox.getSize().x * 0.5f, m_launchBox.getSize().y);
	m_launchBox.setFillColor(sf::Color(99, 79, 23, 230));
	m_launchBox.setPosition(Globals::WIDTH * 0.95f, Globals::HEIGHT * 1.0f);
	m_launchBoxRect = m_launchBox.getGlobalBounds();

	m_launchKicker.setSize(sf::Vector2f(50.0f, 50.0f));
	m_launchKicker.setOrigin(m_launchKicker.getSize().x * 0.5f, m_launchKicker.getSize().y);
	m_launchKicker.setFillColor(sf::Color::Green);
	m_launchKicker.setPosition(Globals::WIDTH * 0.95f, Globals::HEIGHT * 0.16f);
	m_launchKickerRect = m_launchKicker.getGlobalBounds();

	m_noCollideLaunch.setSize(sf::Vector2f(50.0f, 300.0f));
	m_noCollideLaunch.setOrigin(m_noCollideLaunch.getSize().x * 0.5f, m_noCollideLaunch.getSize().y);
	m_noCollideLaunch.setFillColor(sf::Color(0,0,0,200));
	m_noCollideLaunch.setPosition(Globals::WIDTH * 0.95f, Globals::HEIGHT * 1.0f);
	m_noCollideLaunchRect = m_noCollideLaunch.getGlobalBounds();

	m_noCollideGutterA.setSize(sf::Vector2f(150.0f, 80.0f));
	m_noCollideGutterA.setOrigin(m_noCollideGutterA.getSize().x * 0.5f, m_noCollideLaunch.getSize().y);
	m_noCollideGutterA.setFillColor(sf::Color(0, 0, 0, 200));
	m_noCollideGutterA.setPosition(Globals::WIDTH * 0.42f, Globals::HEIGHT * 1.205f);
	m_noCollideGutterARect = m_noCollideGutterA.getGlobalBounds();

	m_gutterTeleport.setSize(sf::Vector2f(150.0f, 20.0f));
	m_gutterTeleport.setOrigin(m_gutterTeleport.getSize().x * 0.5f, m_noCollideLaunch.getSize().y);
	m_gutterTeleport.setFillColor(sf::Color(99, 79, 23, 230));
	m_gutterTeleport.setPosition(Globals::WIDTH * 0.42f, Globals::HEIGHT * 1.28f);
	m_gutterTeleportRect = m_gutterTeleport.getGlobalBounds();

	m_bumper01.setRadius(48.0f);
	m_bumper01.setOrigin(m_bumper01.getRadius(), m_bumper01.getRadius());
	m_bumper01.setFillColor(sf::Color::Cyan);
	m_bumper01.setOutlineColor(sf::Color::Red);
	m_bumper01.setOutlineThickness(-4.0f);
	m_bumper01.setPosition(Globals::WIDTH * 0.5f, Globals::HEIGHT * 0.25f);

	m_roundedTopBot.setRadius(512.0f - 64.0f);
	m_roundedTopBot.setOrigin(m_roundedTopBot.getRadius(), m_roundedTopBot.getRadius());
	m_roundedTopBot.setOutlineColor(sf::Color(26, 32, 39, 200)); // sf::Color::Magenta);
	m_roundedTopBot.setFillColor(sf::Color::Transparent);
	m_roundedTopBot.setOutlineThickness(128.0f);
	m_roundedTopBot.setPosition(Globals::WIDTH * 0.42f, Globals::HEIGHT * 0.45f);

	m_flipperTest.setRadius(80.0f);
	m_flipperTest.setOrigin(m_flipperTest.getRadius(), m_flipperTest.getRadius());
	m_flipperTest.setFillColor(sf::Color(220, 220, 220, 255));
	m_flipperTest.setOutlineColor(sf::Color::Black);
	m_flipperTest.setOutlineThickness(1.0f);
	m_flipperTest.setPosition(Globals::WIDTH * 0.75f, Globals::HEIGHT * 0.80f);
}

Table::~Table()
{
}
