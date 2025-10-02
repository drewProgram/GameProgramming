#include "Vector.h"

#include <print>
#include <cmath>

namespace math {
	Vec2::Vec2()
		: x(0.f), y(0.f)
	{
	}

	Vec2::Vec2(float x, float y)
		: x(x), y(y)
	{
	}

	Vec2 Vec2::Normalize()
	{
		if (x != 0 || y != 0)
		{
			Vec2 normal = *this;

			return normal * (1 / Length());
		}

		std::println("ERROR: can't normalize zero vector");

		return Vec2();
	}

	double Vec2::Length()
	{
		return std::sqrt(x * x + y * y);
	}

	std::string Vec2::ToString()
	{
		std::string out;

		out = "[" + std::to_string(x) + " " + std::to_string(y) + "]";

		return out;
	}

	Vec2 Vec2::operator!()
	{
		Vec2 negatedVector;

		negatedVector.x = x * -1;
		negatedVector.y = y * -1;

		return negatedVector;
	}

	void Vec2::operator+(const Vec2& v2)
	{
		x = x + v2.x;
		y = y + v2.y;
	}

	void Vec2::operator-(const Vec2& v2)
	{
		x = x - v2.x;
		y = y - v2.y;
	}

	void Vec2::operator*(float scalar)
	{
		x = x * scalar;
		y = y * scalar;
	}
}