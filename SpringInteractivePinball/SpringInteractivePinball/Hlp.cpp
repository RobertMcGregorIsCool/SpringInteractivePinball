#include "Hlp.h"

sf::Vector2f Hlp::v2fGetNormal(sf::Vector2f velocity)
{
	float length = v2fGetMagnitude(velocity);
	if (length != 0)
		return sf::Vector2f(velocity.x / length, velocity.y / length);
	else
		return velocity;
}
float Hlp::v2fGetMagnitude(sf::Vector2f velocity)
{
	float length = sqrt(v2fGetMagSquared(velocity));
	return length;
}
float Hlp::v2fGetMagSquared(sf::Vector2f velocity)
{
	return (velocity.x * velocity.x) + (velocity.y * velocity.y);
}

sf::Vector2f Hlp::v2fClamp(float max, float min, sf::Vector2f v2f)
{
	v2f.x = v2f.x > max ? max : v2f.x;
	v2f.x = v2f.x < min ? min : v2f.x;
	v2f.y = v2f.y > max ? max : v2f.y;
	v2f.y = v2f.y < min ? min : v2f.y;
	return v2f;
}

float Hlp::floatLerp(float a, float b, float t)
{
	return a + t * (b - a);
}

sf::Vector2f Hlp::v2fLerp(sf::Vector2f a, sf::Vector2f b, float t)
{
	return sf::Vector2f(floatLerp(a.x, b.x, t), floatLerp(a.y, b.y, t));
}

sf::Vector2f Hlp::v2fAbsolute(sf::Vector2f vector)
{
	float x = std::abs(vector.x);
	float y = std::abs(vector.y);
	return sf::Vector2f(x, y);
}

float Hlp::v2fCrossProduct(sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.y - a.y * b.x;
}

float Hlp::v2fDotProduct(sf::Vector2f lhs, sf::Vector2f rhs)
{
	// return v2fGetMagnitude(lhs) * v2fGetMagnitude(rhs) * cos(v2fCrossProduct(lhs,rhs));
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

sf::Vector2f Hlp::v2fReflect(sf::Vector2f approach, sf::Vector2f normal)
{
	return approach - 2 * v2fDotProduct(approach, normal) * normal;
}

sf::Vector2f Hlp::v2fPerpendicularClockwise(sf::Vector2f vec)
{
	return sf::Vector2f(vec.y, -vec.x);
}

sf::Vector2f Hlp::v2fPerpendicularAntiClockwise(sf::Vector2f vec)
{
	return sf::Vector2f(-vec.y, vec.x);
}

int Hlp::randomRange(int from, int to)
{
	int orderedFrom = std::min(from, to);
	int orderedTo = std::max(to, from);

	int randomNumber = rand() % abs(orderedTo - orderedFrom) + orderedFrom;
	return randomNumber;
}

float Hlp::randomRange(float from, float to)
{
	from *= 100.0f;
	to *= 100.0f;

	float output = static_cast<float>(randomRange(static_cast<int>(from), static_cast<int>(to)));

	return output * 0.01f;
}