/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>

#include "Table.h"

Table::Table()
{
	m_testBox.setOrigin(100.0f, 100.0f);
	m_testBox.setFillColor(sf::Color::Yellow);
	m_testBox.setSize(sf::Vector2f(200.0f, 200.0f));
	m_testBox.setPosition(Globals::WIDTH * 0.5f, Globals::HEIGHT * 0.75f);

	m_testBoxRect = sf::Rect<float>{ sf::Vector2f((Globals::WIDTH * 0.5f) - 100.0f, (Globals::HEIGHT * 0.75f) - 100.0f), m_testBox.getSize() };

	m_bumper01.setRadius(48.0f);
	m_bumper01.setOrigin(m_bumper01.getRadius(), m_bumper01.getRadius());
	m_bumper01.setFillColor(sf::Color::Cyan);
	m_bumper01.setOutlineColor(sf::Color::Red);
	m_bumper01.setOutlineThickness(-4.0f);
	m_bumper01.setPosition(Globals::WIDTH * 0.5f, Globals::HEIGHT * 0.25f);

	m_roundedTopBot.setRadius(512.0f - 32.0f);
	m_roundedTopBot.setOrigin(m_roundedTopBot.getRadius(), m_roundedTopBot.getRadius());
	m_roundedTopBot.setOutlineColor(sf::Color::Magenta);
	m_roundedTopBot.setFillColor(sf::Color::Transparent);
	m_roundedTopBot.setOutlineThickness(100.0f);
	m_roundedTopBot.setPosition(Globals::WIDTH * 0.5f, Globals::HEIGHT * 0.5f);

	m_flipperTest.setRadius(80.0f);
	m_flipperTest.setOrigin(m_flipperTest.getRadius(), m_flipperTest.getRadius());
	m_flipperTest.setFillColor(sf::Color(220, 220, 220, 255));
	m_flipperTest.setOutlineColor(sf::Color::Black);
	m_flipperTest.setOutlineThickness(1.0f);
	m_flipperTest.setPosition(Globals::WIDTH * 0.5f, Globals::HEIGHT * 0.43f);
}

Table::~Table()
{
}
