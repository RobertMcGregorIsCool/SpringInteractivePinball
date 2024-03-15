#include "Render.h"
#include "Collision.h"

Render::Render()
{
}

Render::~Render()
{
}

void Render::render(sf::RenderWindow& t_window, Ball t_balls[4])
{
	t_window.clear(sf::Color::Black);
	t_window.draw(m_floorImage);
	t_window.draw(m_col.m_roundedTopBot);

	t_window.draw(m_backgroundImage);

	t_window.draw(m_col.m_testBox);
	t_window.draw(m_col.m_bumper01);
	t_window.draw(m_col.m_flipperTest);
	t_window.draw(m_col.m_flipperLine);
	t_window.draw(m_col.m_mouseLine);
	t_window.draw(m_col.m_mouseLineReflect);

	t_window.draw(t_balls[0].m_ballShape);

	t_window.draw(m_scoreBoard);

	t_window.display();
}
