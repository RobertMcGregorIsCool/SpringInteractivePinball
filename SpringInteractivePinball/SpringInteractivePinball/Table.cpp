/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>

#include "Table.h"

Table::Table()
{
	m_gutterWallLeft.setSize(sf::Vector2f(20.0f, 90.0f));
	m_gutterWallLeft.setOrigin(m_gutterWallLeft.getSize().x, m_gutterWallLeft.getSize().y);
	m_gutterWallLeft.setFillColor(sf::Color(26, 32, 39, 255)); // sf::Color::Yellow);
	m_gutterWallLeft.setPosition(154.0f, Globals::HEIGHT);
	m_gutterWallLeftRect = m_gutterWallLeft.getGlobalBounds();

	m_gutterWallRigt.setSize(sf::Vector2f(20.0f, 90.0f));
	m_gutterWallRigt.setOrigin(0.0f, m_gutterWallRigt.getSize().y);
	m_gutterWallRigt.setFillColor(sf::Color(26, 32, 39, 255)); // sf::Color::Yellow);
	m_gutterWallRigt.setPosition(350.0f, Globals::HEIGHT);
	m_gutterWallRigtRect = m_gutterWallRigt.getGlobalBounds();

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

	m_noCollideGutterA.setSize(sf::Vector2f(200.0f, 80.0f));
	m_noCollideGutterA.setOrigin(m_noCollideGutterA.getSize().x * 0.5f, m_noCollideLaunch.getSize().y);
	m_noCollideGutterA.setFillColor(sf::Color(0, 0, 0, 200));
	m_noCollideGutterA.setPosition(Globals::WIDTH * 0.42f, Globals::HEIGHT * 1.205f);
	m_noCollideGutterARect = m_noCollideGutterA.getGlobalBounds();

	m_roundedTopBot.setRadius(512.0f - 64.0f);
	m_roundedTopBot.setOrigin(m_roundedTopBot.getRadius(), m_roundedTopBot.getRadius());
	m_roundedTopBot.setOutlineColor(sf::Color(26, 32, 39, 200)); // sf::Color::Magenta);
	m_roundedTopBot.setFillColor(sf::Color::Transparent);
	m_roundedTopBot.setOutlineThickness(256.0f);
	m_roundedTopBot.setPosition(Globals::WIDTH * 0.42f, Globals::HEIGHT * 0.45f);
}

Table::~Table()
{
}
