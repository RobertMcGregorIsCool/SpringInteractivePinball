#pragma once
#include <SFML/Graphics.hpp>

class Hlp
{
public:
	static sf::Vector2f v2fGetNormal(sf::Vector2f velocity);
	static float		v2fGetMagnitude(sf::Vector2f velocity);
	static float		v2fGetMagSquared(sf::Vector2f velocity);
	static sf::Vector2f v2fClamp(float max, float min, sf::Vector2f v2f);
	static float		floatLerp(float a, float b, float t);
	static sf::Vector2f	v2fLerp(sf::Vector2f a, sf::Vector2f b, float t);
	static sf::Vector2f v2fAbsolute(sf::Vector2f vector);
	static float		v2fCrossProduct(sf::Vector2f a, sf::Vector2f b);
	static float		v2fDotProduct(sf::Vector2f lhs, sf::Vector2f rhs);
	static sf::Vector2f v2fReflect(sf::Vector2f approach, sf::Vector2f normal);
	static sf::Vector2f v2fPerpendicularClockwise(sf::Vector2f vec);
	static sf::Vector2f v2fPerpendicularAntiClockwise(sf::Vector2f vec);
	static int			randomRange(int from, int to); // Helper function returns int between two ints. Reacts BADLY to floats.
	static float		randomRange(float from, float to);

};

