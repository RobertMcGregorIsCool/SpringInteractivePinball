#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
public:

	Ball();

	Ball(Game& t_game);
	/*Ball(float t_radius, sf::Vector2f t_startPos);*/
	~Ball();

	//void Initialise(float t_radius, sf::Vector2f t_startPos);

	Game game;

	sf::Sprite ballSprite;
	sf::CircleShape ballShape;
	const float M_RADIUS = 16.0f;

	const sf::Vector2f M_POS_START = sf::Vector2f(300.0f, 500.0f);

	sf::Vector2f m_velocityCur = sf::Vector2f{ 0.0f,0.0f };
	sf::Vector2f m_positionCur = M_POS_START;
	sf::Vector2f m_positionNxt;
	sf::Vector2f m_direction;

	float m_force = 0.0f;
	const float M_GRAVITY = 0.05f;
	const float M_FRICTION = 0.99f;

	/// <summary>
	/// This is called by ForceZones (eg. launcher) and interactables (eg.
	/// flippers, bumpers etc) to add spd to current speed & change dir
	/// </summary>
	/// <param name="dir"></param>
	/// <param name="speed"></param>
	/// <returns></returns>
	void addForce(sf::Vector2f t_dir, float t_speed);

	void bounceCardinal(bool horizontal);

	void move(sf::Time t_deltaTime);

private:
	
};