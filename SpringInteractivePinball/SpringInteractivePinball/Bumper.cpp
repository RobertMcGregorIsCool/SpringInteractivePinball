/// <summary>
/// author Robert McGregor login: c00302210
/// 
/// </summary>
#include "Bumper.h"

Bumper::Bumper(float t_radius, sf::Color t_fill, sf::Color t_line, sf::Color t_hitColor, float t_thickness, sf::Vector2f t_position)
{
	m_bumper.setRadius(48.0f);
	m_bumper.setOrigin(m_bumper.getRadius(), m_bumper.getRadius());
	m_bumper.setFillColor(t_fill);
	m_bumper.setOutlineColor(t_line);
	m_bumper.setOutlineThickness(t_thickness);
	m_bumper.setPosition(t_position);

	m_fill = t_fill;
	m_hitColor = t_hitColor;
}

Bumper::~Bumper(){}

bool Bumper::bumperCheck(Ball& t_ball, sf::Vector2f leadingPoint, sf::Vector2f t_normalisedDir)//, Render t_render)
{
	float bumperColDist = Hlp::v2fGetMagnitude(leadingPoint - m_bumper.getPosition());

	if (bumperColDist < m_bumper.getRadius() + t_ball.M_RADIUS - M_BUMPER_COLLISION_ADJUSTMENT)
	{
		m_bumper.setFillColor(m_hitColor);

		sf::Vector2f bumperNormal = Hlp::v2fGetNormal(m_bumper.getPosition() - t_ball.getPositionCur());

		sf::Vector2f reflectionVec = Hlp::v2fReflect(t_normalisedDir, bumperNormal);

		t_ball.redirect(reflectionVec);

		return true;
	}
	else
	{
		m_bumper.setFillColor(m_fill);
		return false;
	}
}