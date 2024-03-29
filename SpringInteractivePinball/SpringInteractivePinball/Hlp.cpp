/// <summary>
/// Author: Robert McGregor login: c00302210
/// Purpose: Data for pinballs.
/// Date: 28/03/24	Version: 0.1
/// </summary>
#include "Hlp.h"

/// <summary>
/// Gets normalised direction of Vector2f
/// </summary>
/// <param name="velocity">Input value</param>
/// <returns>Normalised direction</returns>
sf::Vector2f Hlp::v2fGetNormal(sf::Vector2f velocity)
{
	float length = v2fGetMagnitude(velocity);
	if (length != 0)
		return sf::Vector2f(velocity.x / length, velocity.y / length);
	else
		return velocity;
}

/// <summary>
/// Get scalar of vector
/// </summary>
/// <param name="velocity">Input value</param>
/// <returns>Vector scalar</returns>
float Hlp::v2fGetMagnitude(sf::Vector2f velocity)
{
	float length = sqrt(v2fGetMagSquared(velocity));
	return length;
}

/// <summary>
/// Get squared mag of vector, faster than GetMagnitude
/// if you can work with these numbers.
/// </summary>
/// <param name="velocity">Input value</param>
/// <returns>Mag squared</returns>
float Hlp::v2fGetMagSquared(sf::Vector2f velocity)
{
	return (velocity.x * velocity.x) + (velocity.y * velocity.y);
}

/// <summary>
/// Clamp a value between two other values
/// </summary>
/// <param name="max">Maximum value</param>
/// <param name="min">Minimum value</param>
/// <param name="v2f"></param>
/// <returns>Clamped value</returns>
sf::Vector2f Hlp::v2fClamp(float max, float min, sf::Vector2f v2f)
{// Do this with Max / Min!
	v2f.x = v2f.x > max ? max : v2f.x;
	v2f.x = v2f.x < min ? min : v2f.x;
	v2f.y = v2f.y > max ? max : v2f.y;
	v2f.y = v2f.y < min ? min : v2f.y;
	return v2f;
}

/// <summary>
/// Straightforward lerp
/// </summary>
/// <param name="a">Starting val</param>
/// <param name="b">Ending val</param>
/// <param name="t">How far along we are from a to b</param>
/// <returns>Current value</returns>
float Hlp::floatLerp(float a, float b, float t)
{
	return a + t * (b - a);
}

/// <summary>
/// Vector2 lerp
/// </summary>
/// <param name="a">Starting val</param>
/// <param name="b">Ending val</param>
/// <param name="t">How far along we are from a to be</param>
/// <returns>Current value</returns>
sf::Vector2f Hlp::v2fLerp(sf::Vector2f a, sf::Vector2f b, float t)
{
	return sf::Vector2f(floatLerp(a.x, b.x, t), floatLerp(a.y, b.y, t));
}

/// <summary>
/// Makes Vector2f absolute positive
/// </summary>
/// <param name="vector">Input vector</param>
/// <returns>Absolute vector2f</returns>
sf::Vector2f Hlp::v2fAbsolute(sf::Vector2f vector)
{
	float x = std::abs(vector.x);
	float y = std::abs(vector.y);
	return sf::Vector2f(x, y);
}

/// <summary>
/// Get cross product
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns>Cross product</returns>
float Hlp::v2fCrossProduct(sf::Vector2f a, sf::Vector2f b)
{
	return a.x * b.y - a.y * b.x;
}

/// <summary>
/// Get Dot product
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns>Dot product</returns>
float Hlp::v2fDotProduct(sf::Vector2f lhs, sf::Vector2f rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

/// <summary>
/// Reflect vector
/// </summary>
/// <param name="approach">Approach vector</param>
/// <param name="normal">Normal vector</param>
/// <returns>Reflected vector</returns>
sf::Vector2f Hlp::v2fReflect(sf::Vector2f approach, sf::Vector2f normal)
{
	return approach - 2 * v2fDotProduct(approach, normal) * normal;
}

/// <summary>
/// Flips vector clockwise
/// </summary>
/// <param name="vec">Input vector</param>
/// <returns>Flipped vector</returns>
sf::Vector2f Hlp::v2fPerpendicularClockwise(sf::Vector2f vec)
{
	return sf::Vector2f(vec.y, -vec.x);
}

/// <summary>
/// Flips vector anti-clockwise
/// </summary>
/// <param name="vec">Input vector</param>
/// <returns>Flipped vector</returns>
sf::Vector2f Hlp::v2fPerpendicularAntiClockwise(sf::Vector2f vec)
{
	return sf::Vector2f(-vec.y, vec.x);
}

/// <summary>
/// Random range between two ints
/// </summary>
/// <param name="from">Start</param>
/// <param name="to">End</param>
/// <returns>Random number</returns>
int Hlp::randomRange(int from, int to)
{
	int orderedFrom = std::min(from, to);
	int orderedTo = std::max(to, from);

	int randomNumber = rand() % abs(orderedTo - orderedFrom) + orderedFrom;
	return randomNumber;
}

/// <summary>
/// Random range between two floats
/// </summary>
/// <param name="from">Start</param>
/// <param name="to">End</param>
/// <returns>Random number</returns>
float Hlp::randomRange(float from, float to)
{
	from *= 1000.0f;
	to *= 1000.0f;

	float output = static_cast<float>(randomRange(static_cast<int>(from), static_cast<int>(to)));

	return output * 0.0001f;
}